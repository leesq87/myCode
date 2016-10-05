using UnityEngine;
using System;
using System.Collections;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{

    public AudioClip pieceSfx;

    private static GameManager _instance;
    private PiecePosition[,] boardState;
	public bool whileMoving = false;
	public bool EnemyWhileMoving = false;

    public Material normalMat;
    public Material selectedMat;

	public bool turn = false;

	GameObject haveTurnGameObject;

	public bool endPromotion = false;

    public GameObject whiteQueen;
    public GameObject whiteRook;
    public GameObject whiteKnight;
    public GameObject whiteBishop;
    public GameObject blackQueen;
    public GameObject blackRook;
    public GameObject blackKnight;
    public GameObject blackBishop;
    Text myTimeText;
    Text enemyTimeText;
    GameObject myPlayer;
    GameObject checkImg;
    GameObject checkmateImg;
    GameObject stalemateImg;
    GameObject timeUpImg;
    GameObject surrenderImg;
    GameObject mainCamera;
    GameObject LeaveRoomWindow;
    Image LeaveRoomWindowBackground;
    public string turnColor;

    public float myTime = 900;
    public float enemyTime = 900;
    bool isTimeUp = false;

    public bool blackMoveAble = false;
    public bool whiteMoveAble = false;

    public int selectPromotionType = 0;
    public static GameManager Instance()
    {
        return _instance;
    }

    void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
        }
        //자신이 white 진영이면 true , black 진영이면 false
    }

    // Use this for initialization
    void Start()
    {
        boardState = new PiecePosition[8, 8];
        UpdateBoardState();
		if (PhotonNetwork.isMasterClient) {
			myPlayer = null;

			//myPlayer.SetActive (false);
		} else {
			myPlayer = PhotonNetwork.Instantiate ("Player", Vector3.zero, Quaternion.identity, 0)as GameObject;
		}
		//Debug.Log (myPlayer.name);

        checkImg = GameObject.Find("CheckImg") ;
        checkmateImg = GameObject.Find("CheckmateImg");
        stalemateImg = GameObject.Find("StalemateImg");
        
        myTimeText = GameObject.Find("MyTimer").GetComponent<Text>();
        enemyTimeText = GameObject.Find("EnemyTimer").GetComponent<Text>();

        if(PhotonNetwork.room.playerCount == 2)
        {
            myTimeText.text = "Time : 15 : 00";
            enemyTime += 30.0f;
        }

    }

    // Update is called once per frame
    void Update()
    {
        Timer();
    }

    /// <summary>
    /// 현재 보드 상태 읽어오는 함수
    /// </summary>
    public void UpdateBoardState()
    {
        //Debug.Log("업데이트");
        GameObject.Find("PiecePosition").BroadcastMessage("ResetDeadZone");
        GameObject.Find("PiecePosition").BroadcastMessage("OnlyCheckDeadZone");
        GameObject.Find("PiecePosition").BroadcastMessage("PieceMovement");
        char[] ch = new char[2];
        for (int i = 0; i < 8; i++)
        {
            ch[0] = Convert.ToChar(('A' + i));
            for (int j = 0; j < 8; j++)
            {
                ch[1] = Convert.ToChar(('1' + j));
                string str = new string(ch);
                GameObject pos = GameObject.Find(str);
                pos.GetComponent<PiecePosition>().stateUpdate();
                boardState[i, j] = pos.GetComponent<PiecePosition>();
                //Debug.Log(boardState[i, j].state);
            }
        }
    }

    public void Timer()
    {
        if (isTimeUp)
            return;

        myTimeText = GameObject.Find("MyTimer").GetComponent<Text>();
        enemyTimeText = GameObject.Find("EnemyTimer").GetComponent<Text>();

        string TimeText;
        int Min, Sec;
        bool isTimeUP = false;

        if (PhotonNetwork.room.playerCount != 2)
            return;

        if (whileMoving || EnemyWhileMoving)
            return;

        if(turn)
        {
            myTime -= Time.deltaTime;
            if (myTime <= 0)
            {
                myTime = 0;
                isTimeUP = true;
            }

            Min = (int)(myTime / 60);
            Sec = (int)(myTime % 60);
            TimeText = "Time : " + Min + " : " + Sec;
            myTimeText.text = TimeText;
        }
        else
        {
            enemyTime -= Time.deltaTime;
            if (enemyTime <= 0)
                enemyTime = 0;

            Min = (int)(enemyTime / 60);
            Sec = (int)(enemyTime % 60);
            TimeText = "Time : " + Min + " : " + Sec;
            enemyTimeText.text = TimeText;
        }

        if(isTimeUP)
        {
            myPlayer.GetComponent<Player>().TimeUp();
            isTimeUp = true;
        }

    }

    public IEnumerator Promotion(GameObject seletedBoard, GameObject pawn)
    {

        GameObject newPiecePos = seletedBoard;
        GameObject temp = GameObject.Find("PromotionSpace");

        pawn.transform.parent = temp.transform;




        GameObject newPiece;
        if (pawn.layer == 10)
		{
			yield return myPlayer.GetComponent<Player> ().selectPromotion ("Black");
			//Debug.Log ("매니저" + selectPromotionType);
            switch(selectPromotionType)
            {
                case 1:
                    newPiece = Instantiate(blackQueen, Vector3.zero, Quaternion.identity) as GameObject;
                    break;
                case 2:
                    newPiece = Instantiate(blackRook, Vector3.zero, Quaternion.identity) as GameObject;
                    break;
                case 3:
                    newPiece = Instantiate(blackBishop, Vector3.zero, Quaternion.identity) as GameObject;
                    break;
                case 4:
                    newPiece = Instantiate(blackKnight, Vector3.zero, Quaternion.identity) as GameObject;
                    break;
                default:
                    newPiece = Instantiate(blackKnight, Vector3.zero, Quaternion.identity) as GameObject;
                    break;
            }
            
			//endPromotion = false;
        }
        else
        {
			yield return myPlayer.GetComponent<Player> ().selectPromotion ("White");
            switch (selectPromotionType)
            {
                case 1:
                    newPiece = Instantiate(whiteQueen, Vector3.zero, Quaternion.identity) as GameObject;
                    break;
                case 2:
                    newPiece = Instantiate(whiteRook, Vector3.zero, Quaternion.identity) as GameObject;
                    break;
                case 3:
                    newPiece = Instantiate(whiteBishop, Vector3.zero, Quaternion.identity) as GameObject;
                    break;
                case 4:
                    newPiece = Instantiate(whiteKnight, Vector3.zero, Quaternion.identity) as GameObject;
                    break;
                default:
                    newPiece = Instantiate(whiteKnight, Vector3.zero, Quaternion.identity) as GameObject;
                    break;
            }

			//endPromotion = false;
        }


        Debug.Log("생성한 피스이름" + newPiece.name);

        newPiece.transform.parent = newPiecePos.transform;
        Debug.Log("새로운 부모이름" + newPiece.transform.parent.name);
        newPiece.transform.position = newPiece.transform.parent.position;

        newPiece.SendMessage("SetPosition");

        //Debug.Log("겟포지션"+newPiece.GetComponent<Rook>().ConvertPosition(newPiece.GetComponent<Rook>().currentPosition));
        Destroy(pawn.gameObject, 0.2f);
        //Debug.Log("이거 다음");
        yield return true;
    }

    public IEnumerator MovingPiece(GameObject selectPiece,GameObject selectBoard)
    {
        bool isPromotion = false;

		whileMoving = true;
		myPlayer.GetComponent<Player> ().MovementAnimation (true);
        GameObject RookTmp, BoardTmp;
        RookTmp = null;
        BoardTmp = null;

        GameObject.Find("PiecePosition").BroadcastMessage("NextTurn");

        if (selectPiece.GetComponent<Pawn>())
        {
            // 원래 위치
            int[] originalPos = new int[2];
            originalPos = selectPiece.GetComponent<Pawn>().GetPosition(selectPiece.transform.parent.name);

            // 이동 위치
            int[] transPos = new int[2];
            string str = selectBoard.name;

            // 선택한 폰이 처음 움직이는 거라면
            if (selectPiece.GetComponent<Pawn>().isFirstMove)
            {
                transPos[0] = (str[0] - 'A');
                transPos[1] = (str[1] - '1');

                // 2칸 이동 했으면
                if (Math.Abs(originalPos[1] - transPos[1]) > 1)
                {
                    selectPiece.GetComponent<Pawn>().isDoubleMove = true;
                }
                selectPiece.GetComponent<Pawn>().isFirstMove = false;
            }

            bool isDiagonalMove = false;

            originalPos = selectPiece.GetComponent<Pawn>().GetPosition(selectPiece.transform.parent.name);
            str = selectBoard.name;
            transPos[0] = (str[0] - 'A');
            transPos[1] = (str[1] - '1');

            // 대각선 이동했는지 검사
            if (Math.Abs(originalPos[1] - transPos[1]) > 0)
            {
                if (Math.Abs(originalPos[0] - transPos[0]) > 0)
                {
                    isDiagonalMove = true;
                }
            }
            // 대각선 이동이 맞으면
            if (isDiagonalMove)
            {
                // 이동한 곳에 자식이 있으면 그냥 대각선 이동
                if (selectBoard.transform.childCount > 0)
                {

                }
                // 자식이 없으면 양파상 이동
                else
                {
                    // 선택한 폰이 블랙
                    if (selectPiece.layer == 10)
                    {
                        transPos[1] = transPos[1] + 1;
                    }
                    else
                    {
                        transPos[1] = transPos[1] - 1;
                    }

                    string destroyPos = selectPiece.GetComponent<Pawn>().ConvertPosition(transPos);

                    Transform child = GameObject.Find(destroyPos).transform.GetChild(0);
                    GameObject temp = GameObject.Find("TmpSpace");
                    child.transform.parent = temp.transform;
                    Destroy(child.gameObject, 1.0f);
                }
            }

            if (selectPiece.layer == 10)
            {
                if (transPos[1] == 0)
                {
                    //Debug.Log("블랙이 프로모션한다");
                    isPromotion = true;
                }
            }
            // 화이트
            else
            {
                if (transPos[1] == 7)
                {
                    //Debug.Log("화이트가 프로모션한다");
                    isPromotion = true;
                    
                }
            }
        }
        else if(selectPiece.GetComponent<Rook>())
        {
            selectPiece.GetComponent<Rook>().isFirstMove = false;
        }
        else if(selectPiece.GetComponent<King>())
        {
            // 원래 위치
            int[] originalPos = new int[2];
            originalPos = selectPiece.GetComponent<King>().GetPosition(selectPiece.transform.parent.name);

            // 이동 위치
            int[] transPos = new int[2];
            string str = selectBoard.name;

            // 킹을 처음 움직이는 거라면
            if (selectPiece.GetComponent<King>().isFirstMove)
            {
                transPos[0] = (str[0] - 'A');
                transPos[1] = (str[1] - '1');

                Debug.Log(Math.Abs(originalPos[0] - transPos[0]));
                // 2칸 이동 했으면 (캐슬링 했으면)
                if (Math.Abs(originalPos[0] - transPos[0]) > 1)
                {
                    // 킹 사이드 캐슬링
                    if(originalPos[0] - transPos[0] < 0)
                    {
                        // 블랙
                        if (selectPiece.layer == 10)
                        {
                            RookTmp = GameObject.Find("H8").transform.GetChild(0).gameObject;
                            RookTmp.GetComponent<Rook>().isFirstMove = false;
                            BoardTmp = GameObject.Find("F8");
                        }
                        // 화이트
                        else
                        {
                            RookTmp = GameObject.Find("H1").transform.GetChild(0).gameObject;
                            RookTmp.GetComponent<Rook>().isFirstMove = false;
                            BoardTmp = GameObject.Find("F1");
                        }
                    }
                    // 퀸 사이드 캐슬링
                    else
                    {
                        // 블랙
                        if (selectPiece.layer == 10)
                        {
                            RookTmp = GameObject.Find("A8").transform.GetChild(0).gameObject;
                            RookTmp.GetComponent<Rook>().isFirstMove = false;
                            BoardTmp = GameObject.Find("D8");
                        }
                        // 화이트
                        else
                        {
                            RookTmp = GameObject.Find("A1").transform.GetChild(0).gameObject;
                            RookTmp.GetComponent<Rook>().isFirstMove = false;
                            BoardTmp = GameObject.Find("D1");
                        }
                    }
                }
                selectPiece.GetComponent<King>().isFirstMove = false;
            }
        }

        if (selectBoard.transform.childCount > 0)
        {
            Transform child = selectBoard.transform.GetChild(0);
			if (child.gameObject.layer != selectPiece.layer)
            {
                //이동시 해당 칸에 적군 기물 존재시 적군 기물삭제
                GameObject temp = GameObject.Find("TmpSpace");
                child.transform.parent = temp.transform;
                Destroy(child.gameObject, 1.0f);
            }
        }

        // 기물 움직임 애니메이션 시작  ===========================================================

        if (selectPiece.GetComponent<King>())
        {
            yield return MovingAnimation(selectPiece, selectBoard);
            if(RookTmp != null && BoardTmp != null)
                yield return MovingAnimation(RookTmp, BoardTmp);
        }
        else
        {
            yield return MovingAnimation(selectPiece, selectBoard);
        }

        // 애니메이션 끝 ===========================================================

        // 애니메이션 끝나고 프로모션 호출
        if(isPromotion)
        {
            //Debug.Log("프로모션" + selectBoard.name + "" + selectPiece.name);
            yield return Promotion(selectBoard, selectPiece);
            //Debug.Log("이거");
        }


		whileMoving = false;
		myPlayer.GetComponent<Player> ().MovementAnimation (false);
		UpdateBoardState();

        yield return true;
    }

    /// <summary>
    /// 기물 움직임 애니메이션 코루틴
    /// </summary>
    /// <param name="selected">
    /// 움직일 기물 GameObject
    /// </param>
    /// <param name="target">
    /// 움직일 위치 GameObject
    /// </param>
    /// <returns></returns>
    IEnumerator MovingAnimation(GameObject selected, GameObject target)
    {
        selected.GetComponent<Renderer>().material = normalMat;

        Vector3 rot = selected.transform.rotation.eulerAngles;
        Vector3 target_pos = target.transform.position;
        Vector3 target_up_pos = new Vector3(target_pos.x, target_pos.y + 2.5f, target_pos.z);
        // 기물을 위로 들어올림
        for (int i = 0; i < 5; i++)
        {
            Vector3 piece_pos = selected.transform.localPosition;
            piece_pos.z -= 0.5f;
            selected.transform.localPosition = piece_pos;
            yield return new WaitForEndOfFrame();
        }
        // 기물을 회전시킴
        for (int i = 0; i < 30; i++)
        {
            if (selected.layer == 9)
            {
                rot.x += 1;
            }
            else
            {
                rot.x -= 1;
            }

            selected.transform.rotation = Quaternion.Euler(rot);
            yield return new WaitForSeconds(0.005f);
        }
        // 목표위치 위로 이동
        for (int i = 1; i <= 50; i++)
        {
            selected.transform.position = Vector3.Lerp(selected.transform.position, target_up_pos, 0.02f * i);
            if (Vector3.Distance(selected.transform.position, target_up_pos) < 1)
            {
                selected.transform.position = target_up_pos;
                break;
            }
            yield return new WaitForEndOfFrame();
        }
        // 기물을 다시 원래대로 회전시킴
        for (int i = 0; i < 30; i++)
        {
            if (selected.layer == 9)
            {
                rot.x -= 1;
            }
            else
            {
                rot.x += 1;
            }

            selected.transform.rotation = Quaternion.Euler(rot);
            yield return new WaitForSeconds(0.005f);
        }
        // 기물을 아래로 내림
        for (int i = 0; i < 5; i++)
        {
            Vector3 piece_pos = selected.transform.localPosition;
            piece_pos.z += 0.5f;
            selected.transform.localPosition = piece_pos;
            yield return new WaitForEndOfFrame();
        }

        AudioManager.Instance().PlaySfx(pieceSfx);
 
        selected.transform.parent = target.transform;
        selected.transform.position = selected.transform.parent.position;

        yield return true;
    }

	public void FindPlayer()
	{
		myPlayer = GameObject.Find ("Player(Clone)");
	}

    public int CheckState()
    {
        if (PhotonNetwork.room.playerCount != 2)
            return 0;

        // 화이트 플레이어
        if (myPlayer.GetComponent<Player>().playerColor == "White")
        {
            string whiteKing = GameObject.FindWithTag("WhiteKing").transform.parent.name;
            // 한개라도 이동할 수 있다
            Debug.Log("whiteMoveAble : " + whiteMoveAble);
            if (whiteMoveAble)
            {
                //Debug.Log("화이트 이동할 수 있다");
                myPlayer.GetComponent<Player>().pv.RPC("initMoveAble", PhotonTargets.All);
                //whiteMoveAble = false;
                //blackMoveAble = false;

                // 왕이 데드존이면 체크상태
                if (GameObject.Find(whiteKing).GetComponent<PiecePosition>().whiteDead)
                    return 1;
                // 아무상태아님
                else
                    return 0;
            }
            // 하나도 이동할 수 없다.
            // 체크메이트인지 스테일메이트인지 체크
            else
            {
                //Debug.Log("화이트 이동할 수 없다");
                myPlayer.GetComponent<Player>().pv.RPC("initMoveAble", PhotonTargets.All);
                // whiteMoveAble = false;
                // blackMoveAble = false;

                // 왕의위치가 데드존이면 체크메이트
                if (GameObject.Find(whiteKing).GetComponent<PiecePosition>().whiteDead)
                    return 2;
                // 데드존이 아니면 스테일메이트
                else
                    return 3;
            }

        }
        // 블랙 플레이어
        else
        {
            string blackKing = GameObject.FindWithTag("BlackKing").transform.parent.name;
            // 한개라도 이동할 수 있다
			if (blackMoveAble)
            {
                //whiteMoveAble = false;
                // blackMoveAble = false;
                myPlayer.GetComponent<Player>().pv.RPC("initMoveAble", PhotonTargets.All);
                // 왕이 데드존이면 체크상태
                if (GameObject.Find(blackKing).GetComponent<PiecePosition>().blackDead)
                    return 1;
                // 아무상태아님
                else
                    return 0;
            }
            // 하나도 이동할 수 없다.
            // 체크메이트인지 스테일메이트인지 체크
            else
            {
                //whiteMoveAble = false;
                //blackMoveAble = false;
                myPlayer.GetComponent<Player>().pv.RPC("initMoveAble", PhotonTargets.All);
                // 왕의위치가 데드존이면 체크메이트
                if (GameObject.Find(blackKing).GetComponent<PiecePosition>().blackDead)
                    return 2;
                // 데드존이 아니면 스테일메이트
                else
                    return 3;
            }
        }
    }

    public IEnumerator CheckAnimation()
    {
		checkImg = GameObject.Find("CheckImg") ;
        Vector3 checkScale = checkImg.transform.localScale;

        for(int i = 0; i < 10; i++)
        {
            checkScale.y += 0.1f;
            checkImg.transform.localScale = checkScale;
            yield return new WaitForEndOfFrame();
        }
        yield return new WaitForSeconds(0.8f);
        for (int i = 0; i < 10; i++)
        {
            checkScale.y -= 0.1f;
            checkImg.transform.localScale = checkScale;
            yield return new WaitForEndOfFrame();
        }

        yield return true;
    }

    public IEnumerator CheckmateAnimation(bool win)
    {
        GameObject outcome;
        GameObject btnBackToLobby;
		checkmateImg = GameObject.Find("CheckmateImg");
        btnBackToLobby = GameObject.Find("BtnBackToLobby");
        Vector3 checkScale = checkmateImg.transform.localScale;
        Vector3 btnScale = btnBackToLobby.transform.localScale;

        for (int i = 0; i < 10; i++)
        {
            checkScale.y += 0.1f;
            checkmateImg.transform.localScale = checkScale;
            yield return new WaitForEndOfFrame();
        }
        StartCoroutine(CameraShakeProcess(1.0f, 0.5f));
        yield return new WaitForSeconds(1.5f);
        if (win)
        {
            outcome = GameObject.Find("WinImg");
        }
        else
        {
            outcome = GameObject.Find("LoseImg");
        }

        Vector3 outcomeScale = outcome.transform.localScale;

        for (int i = 0; i < 10; i++)
        {
            outcomeScale.x += 0.1f;
            outcome.transform.localScale = outcomeScale;
            yield return new WaitForEndOfFrame();
        }

        yield return new WaitForSeconds(1.0f);

        for (int i = 0; i < 10; i++)
        {
            btnScale.x += 0.1f;
            btnScale.y += 0.1f;
            btnBackToLobby.transform.localScale = btnScale;
            yield return new WaitForEndOfFrame();
        }

        yield return true;
    }

    public IEnumerator StalemateAnimation()
    {
        GameObject btnBackToLobby;
        stalemateImg = GameObject.Find("StalemateImg");
        btnBackToLobby = GameObject.Find("BtnBackToLobby");
        Vector3 staleScale = stalemateImg.transform.localScale;
        Vector3 btnScale = btnBackToLobby.transform.localScale;

        for (int i = 0; i < 10; i++)
        {
            staleScale.y += 0.1f;
            stalemateImg.transform.localScale = staleScale;
            yield return new WaitForEndOfFrame();
        }

        yield return new WaitForSeconds(1.0f);

        for (int i = 0; i < 10; i++)
        {
            btnScale.x += 0.1f;
            btnScale.y += 0.1f;
            btnBackToLobby.transform.localScale = btnScale;
            yield return new WaitForEndOfFrame();
        }

        yield return true;
    }

    public IEnumerator SurrenderAnimation()
    {
        GameObject btnBackToLobby;
        surrenderImg = GameObject.Find("SurrenderImg");
        btnBackToLobby = GameObject.Find("BtnBackToLobby");
        Vector3 surrenderScale = surrenderImg.transform.localScale;
        Vector3 btnScale = btnBackToLobby.transform.localScale;

        for (int i = 0; i < 10; i++)
        {
            surrenderScale.y += 0.1f;
            surrenderImg.transform.localScale = surrenderScale;
            yield return new WaitForEndOfFrame();
        }

        for (int i = 0; i < 10; i++)
        {
            btnScale.x += 0.1f;
            btnScale.y += 0.1f;
            btnBackToLobby.transform.localScale = btnScale;
            yield return new WaitForEndOfFrame();
        }
        yield return true;
    }

    public IEnumerator TimeUpAnimation(bool win)
    {
        GameObject outcome;
        GameObject btnBackToLobby;
        timeUpImg = GameObject.Find("TimeUpImg");
        btnBackToLobby = GameObject.Find("BtnBackToLobby");
        Vector3 timeUpScale = timeUpImg.transform.localScale;
        Vector3 btnScale = btnBackToLobby.transform.localScale;

        for (int i = 0; i < 10; i++)
        {
            timeUpScale.y += 0.1f;
            timeUpImg.transform.localScale = timeUpScale;
            yield return new WaitForEndOfFrame();
        }
        StartCoroutine(CameraShakeProcess(0.8f, 0.25f));
        yield return new WaitForSeconds(1.0f);
        if (win)
        {
            outcome = GameObject.Find("WinImg");
        }
        else
        {
            outcome = GameObject.Find("LoseImg");
        }

        Vector3 outcomeScale = outcome.transform.localScale;

        for (int i = 0; i < 10; i++)
        {
            outcomeScale.x += 0.1f;
            outcome.transform.localScale = outcomeScale;
            yield return new WaitForEndOfFrame();
        }

        yield return new WaitForSeconds(1.0f);

        for (int i = 0; i < 10; i++)
        {
            btnScale.x += 0.1f;
            btnScale.y += 0.1f;
            btnBackToLobby.transform.localScale = btnScale;
            yield return new WaitForEndOfFrame();
        }

        yield return true;
    }

    IEnumerator CameraShakeProcess(float shakeTime, float shakeSense)
    {
        mainCamera = GameObject.Find("Center");
        Vector3 camDefaultPos = mainCamera.transform.localPosition;
        float deltaTime = 0.0f;
        while (deltaTime < shakeTime)
        {
            deltaTime += Time.deltaTime;
            mainCamera.transform.localPosition = camDefaultPos;

            Vector3 pos = Vector3.zero;
            pos.x = UnityEngine.Random.Range(-shakeSense, shakeSense);
            pos.y = UnityEngine.Random.Range(-shakeSense, shakeSense);
            //pos.z = Random.Range (-shakeSense, shakeSense);

            mainCamera.transform.localPosition += pos;

            yield return new WaitForEndOfFrame();
        }
        mainCamera.transform.localPosition = camDefaultPos;
    }

    public void BtnQueen()
    {
        myPlayer.GetComponent<Player>().PromotionQueen();
    }

    public void BtnRook()
    {
        myPlayer.GetComponent<Player>().PromotionRook();
    }

    public void BtnBishop()
    {
        myPlayer.GetComponent<Player>().PromotionBishop();
    }

    public void BtnKnight()
    {
        myPlayer.GetComponent<Player>().PromotionKnight();
    }

    public void BtnBackToLobby()
    {
		GameObject.Find ("PhotonManager").GetComponent<MainPhotonInit> ().BackToLobby ();
    }

    public void BtnSurrender()
    {
        if(PhotonNetwork.room.playerCount != 2)
        {
            GameObject.Find("PhotonManager").GetComponent<MainPhotonInit>().BackToLobby();
        }
        else
        {
            StartCoroutine(myPlayer.GetComponent<Player>().DoSurrender());
        }
    }

    public void BtnLeaveRoomWindowOpen()
    {
        LeaveRoomWindow = GameObject.Find("LeaveRoom");
        LeaveRoomWindowBackground = GameObject.Find("LeaveRoomBackground").GetComponent<Image>();
        LeaveRoomWindowBackground.enabled = true;
        StartCoroutine(OpenWindow(LeaveRoomWindow));
    }

    public void BtnLeaveRoomWindowClose()
    {
        LeaveRoomWindowBackground.enabled = false;
        StartCoroutine(CloseWindow(LeaveRoomWindow));
    }

    IEnumerator OpenWindow(GameObject window)
    {
        Vector3 windowScale = window.transform.localScale;

        for(int i = 0; i < 40; i++)
        {
            windowScale.y += 0.025f;
            window.transform.localScale = windowScale;
            yield return new WaitForEndOfFrame();
        }
        windowScale.y = 1.0f;
        window.transform.localScale = windowScale;
    }

    IEnumerator CloseWindow(GameObject window)
    {
        Vector3 windowScale = window.transform.localScale;

        for (int i = 0; i < 10; i++)
        {
            windowScale.y -= 0.1f;
            window.transform.localScale = windowScale;
            yield return new WaitForEndOfFrame();
        }
        windowScale.y = 0.0f;
        window.transform.localScale = windowScale;
    }

}
