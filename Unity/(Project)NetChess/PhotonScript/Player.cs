using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Player : MonoBehaviour {

	public playerState state;
	public enum playerState
	{
		enemyTurn,
		choicePiece,
		choiceMovePiece,
		actionWait,
		action
	};
    public Material normalMat;
    public Material selectedMat;
    public PhotonView pv;
    public string playerColor = "White";
    public string enemyColor = "Black";

    Text turntext;
    GameObject turnImg;
    GameObject promotionWindow;
    GameObject selectPiece;
	GameObject selectBoard;

	int selectPromotionTypeNum = 0;

	bool playerWhite;
	bool myColor;
    bool waitForTurn = false;
	bool stop = true;

	void Awake()
	{
		//GameObject.FindGameObjectsWithTag()
		pv = gameObject.GetComponent<PhotonView> ();
		state = playerState.enemyTurn;

		myColor = PhotonNetwork.isMasterClient;
		if (myColor)
		{
			playerColor = "White";
			enemyColor = "Black";
		}
		else
		{
			playerColor = "Black";
			enemyColor = "White";
		}
	}
	// Use this for initialization
	void Start () {
		turntext = GameObject.Find ("WhoTurn").GetComponent<Text>();
        turnImg = GameObject.Find("MyTurnImg");
        promotionWindow = GameObject.Find("PromotionWindow");
        //playerWhite = GameManager.Instance ().playerWhite;
        if (myColor) {
            GameManager.Instance().turn = true;
            GameManager.Instance().myTime += 30.0f;
            myTurn ();
        }
		else
		{
			pv.RPC ("SecendPlayerLogin", PhotonTargets.Others);
            turntext.text = "EnemyTrun";
			GameObject camera = GameObject.Find("Camera");
			camera.transform.rotation = Quaternion.Euler(0, 180.0f, 0);
		}
	}
	
	// Update is called once per frame
	void Update () {
		PieceTouchCheck ();
	}

	/// <summary>
	/// <br>
	/// 플레이어 상태 전환 함수
	/// 기물 터치 및 이동 보드 선택
	/// <para>
	/// enemyTurn : 상대 플레이어 턴 - 신호가 올때 까지 대기
	/// choicePiece : 내 턴 - 이동 할 기물 선택 가능
	/// choiceMovePiece : 이동 할 기물 선택후 - 기물 재선택 또는 경로 설정 가능
	/// actionWait : 플레이 버튼 입력 까지 대기
	/// action : 플레이 버튼 입력 - 이동 처리
	/// </para>
	/// </summary>
	void PieceTouchCheck()
    {
        switch (state)
        {
            case playerState.enemyTurn:
                if (stop)
                {
                    return;
                }

                if (GameManager.Instance().whileMoving)
                {
                    return;
                }
                state = playerState.choicePiece;


                break;
            case playerState.choicePiece:
                if (Input.GetButtonDown("Fire1"))
                {
                    Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
                    RaycastHit hit;
                    //자군 진영 색과 같은 기물만 선택(터치) 가능
                    int layerMask = (1 << LayerMask.NameToLayer(playerColor));
                    if (Physics.Raycast(ray, out hit, Mathf.Infinity, layerMask))
                    {
                        if (hit.transform.tag == playerColor + "Piece" || hit.transform.tag == playerColor + "King")
                        {
                            selectPiece = hit.transform.gameObject;
                            ShowMoveAble(true);
                            selectPiece.GetComponent<Renderer>().material = selectedMat;
                            state = playerState.choiceMovePiece;
                            break;
                        }
                    }
                }
                break;
            case playerState.choiceMovePiece:
                if (Input.GetButtonDown("Fire1"))
                {
                    Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
                    RaycastHit hit;
                    if (Physics.Raycast(ray, out hit))
                    {
                        if (hit.transform.tag == playerColor + "Piece" || hit.transform.tag == playerColor + "King")
                        {
                            //아군기물 재선택

                            //이동 가능 범위 표시 제거(selectPiece)
                            ShowMoveAble(false);
                            selectPiece.GetComponent<Renderer>().material = normalMat;

                            selectPiece = hit.transform.gameObject;
                            //재선택 된 기물 이동가능 범위 표시(selectPiece)
                            ShowMoveAble(true);
                            selectPiece.GetComponent<Renderer>().material = selectedMat;
                            state = playerState.choiceMovePiece;
                            return;
                        }
                    }
                    int layerMask = 1 << 8;
                    if (Physics.Raycast(ray, out hit, Mathf.Infinity, layerMask))
                    {
                        if (hit.transform.childCount > 0)
                        {
                            Transform selectBoardChild = hit.transform.GetChild(0);
                            if (selectBoardChild.tag == playerColor + "Piece" || selectBoardChild.tag == playerColor + "King")
                            {
                                //이동 가능 범위 표시 제거(selectPiece)
                                ShowMoveAble(false);
                                selectPiece.GetComponent<Renderer>().material = normalMat;
                                //아군기물이 존재하는 칸 선택시 해당 기물 재선택
                                selectPiece = selectBoardChild.transform.gameObject;
                                //재선택 된 기물 이동가능 범위 표시(selectPiece)
                                ShowMoveAble(true);
                                selectPiece.GetComponent<Renderer>().material = selectedMat;
                                return;
                            }
                        }
                        selectBoard = hit.transform.gameObject;
                        if (selectBoard.name == "Plane")
                        {
                            ShowMoveAble(false);
                            selectPiece.GetComponent<Renderer>().material = normalMat;
                            selectBoard = null;
                            selectPiece = null;
                            state = playerState.choicePiece;
                            return;
                        }
                        else
                        {
                            if (selectBoard.GetComponent<SpriteRenderer>().enabled)
                            {

                            }
                            else
                            {
                                ShowMoveAble(false);
                                selectPiece.GetComponent<Renderer>().material = normalMat;
                                selectBoard = null;
                                selectPiece = null;
                                state = playerState.choicePiece;
                                return;
                            }
                        }

                        state = playerState.actionWait;
                    }
                }
                break;
            case playerState.actionWait:
                //플레이 버튼 입력 까지 대기
                //플레이 버튼 입력시 이동 가능 범위 표시 제거(selectPiece)

                ShowMoveAble(false);
                state = playerState.action;
                break;
            case playerState.action:
                //플레이 버튼 입력 후

                stop = true;
                GameManager.Instance().turn = false;

                turntext.text = "EnemyTurn";
                if (!waitForTurn)
                {
                    pv.RPC("SendMove", PhotonTargets.All, GetPositionStr(selectPiece), GetPositionStr(selectBoard));
                    waitForTurn = true;
                }

                if (GameManager.Instance().whileMoving || GameManager.Instance().EnemyWhileMoving)
                {
                    return;
                }

                float time = GameManager.Instance().myTime;
                GameManager.Instance().enemyTime += 30.0f;
                pv.RPC("PushMyTime", PhotonTargets.Others, time);

                pv.RPC("myTurn", PhotonTargets.Others);
                waitForTurn = false;
                state = playerState.enemyTurn;
                break;
        }
    }

    public void MovementAnimation(bool start)
	{
		if (start) 
		{
			pv.RPC ("StartMoving",PhotonTargets.Others);
		} 
		else 
		{
			pv.RPC ("EndMoving",PhotonTargets.Others);
		}

	}

    public void TimeUp()
    {
        stop = true;
        StartCoroutine(GameManager.Instance().TimeUpAnimation(false));
        pv.RPC("PushTimeUpResult", PhotonTargets.Others);
    }

    [PunRPC]
    void PushTimeUpResult()
    {
        stop = true;
        StartCoroutine(GameManager.Instance().TimeUpAnimation(true));
    }

    public IEnumerator DoSurrender()
    {
        pv.RPC("Surrender", PhotonTargets.Others);

        yield return new WaitForSeconds(0.25f);

        GameObject.Find("PhotonManager").GetComponent<MainPhotonInit>().BackToLobby();
    }

    [PunRPC]
    void Surrender()
    {
        stop = true;
        StartCoroutine(GameManager.Instance().SurrenderAnimation());
    }

    [PunRPC]
    void PushMyTime(float time)
    {
        GameManager.Instance().turn = true;
        GameManager.Instance().myTime += 30.0f;
        GameManager.Instance().enemyTime = time;
    }

	[PunRPC]
	void StartMoving()
	{
		GameManager.Instance().EnemyWhileMoving = true;
	}

	[PunRPC]
	void EndMoving()
	{
		GameManager.Instance().EnemyWhileMoving = false;
	}

	/// <summary>
	/// 기물 이동 경로 표시 함수(on/off)
	/// </summary>
	/// <param name="onoff"> 선택시(true),해제시(false) </param>
	void ShowMoveAble(bool onoff)
	{
		if (onoff)
		{
			if (selectPiece.GetComponent<Pawn>())
			{
				selectPiece.GetComponent<Pawn>().ShowMoveAbleOn();
			}
			if (selectPiece.GetComponent<Knight>())
			{
				selectPiece.GetComponent<Knight>().ShowMoveAbleOn();
			}
			if (selectPiece.GetComponent<Bishop>())
			{
				selectPiece.GetComponent<Bishop>().ShowMoveAbleOn();
			}
			if (selectPiece.GetComponent<Rook>())
			{
				selectPiece.GetComponent<Rook>().ShowMoveAbleOn();
			}
			if (selectPiece.GetComponent<Queen>())
			{
				selectPiece.GetComponent<Queen>().ShowMoveAbleOn();
			}
			if (selectPiece.GetComponent<King>())
			{
				selectPiece.GetComponent<King>().ShowMoveAbleOn();
			}
		}
		else {
			if (selectPiece.GetComponent<Pawn>())
			{
				selectPiece.GetComponent<Pawn>().ShowMoveAbleOff();
			}
			if (selectPiece.GetComponent<Knight>())
			{
				selectPiece.GetComponent<Knight>().ShowMoveAbleOff();
			}
			if (selectPiece.GetComponent<Bishop>())
			{
				selectPiece.GetComponent<Bishop>().ShowMoveAbleOff();
			}
			if (selectPiece.GetComponent<Rook>())
			{
				selectPiece.GetComponent<Rook>().ShowMoveAbleOff();
			}
			if (selectPiece.GetComponent<Queen>())
			{
				selectPiece.GetComponent<Queen>().ShowMoveAbleOff();
			}
			if (selectPiece.GetComponent<King>())
			{
				selectPiece.GetComponent<King>().ShowMoveAbleOff();

			}
		}
	}

	/// <summary>
	/// <br>
	/// 이동 경로를 상대방 클라이언트에게 보내는 함수
	/// string값을 보내 변환 및 처리
	/// </summary>
	/// <param name="piece">이동 시킬 기물이 있는 보드의 이름</param>
	/// <param name="board">이동할 보드의 이름</param>
	[PunRPC]
	void SendMove(string piece, string board)
	{
		GameObject PieceObj = GameObject.Find (piece);
		GameObject selectPieceRPC = PieceObj.transform.GetChild (0).gameObject;
		GameObject selectBoardRPC = GameObject.Find (board);
		StartCoroutine (GameManager.Instance ().MovingPiece (selectPieceRPC, selectBoardRPC));


		//StartCoroutine (GameManager.Instance ().MovingPiece (GetPositionChildObj (piece), GetPositionObj (board)));
	}

	/// <summary>
	/// <br>
	/// 기물 및 보드를 string 값으로 변환하는 함수
	/// </summary>
	/// <returns>GameObject의 이름을 string로 변환하여 반환</returns>
	/// <param name="obj">해당 GameObject</param>
	string GetPositionStr(GameObject obj)
	{
		string str;
		if (obj.transform.parent.name == "PiecePosition") {
			str = obj.name;
		} else {
			str = obj.transform.parent.name;
		}
		return str;
	}

	/// <summary>
	/// string값(position) 검색 GameObject로 변환
	/// </summary>
	/// <returns>The position object.</returns>
	/// <param name="obj">해당 GameObject의 string</param>
	GameObject GetPositionObj(string obj)
	{
		//현재 사용X
		GameObject targetObj = GameObject.Find (obj);

		return targetObj;
	}

	/// <summary>
	/// string값(position) 검색 GameObject로 변환
	/// </summary>
	/// <returns>The position object.</returns>
	/// <param name="obj">해당 GameObject의 string</param>
	GameObject GetPositionChildObj(string obj)
	{
		//현재 사용X
		GameObject targetChildObj = GameObject.Find (obj).transform.GetChild (0).gameObject;

		return targetChildObj;
	}

	[PunRPC]
	void myTurn()
	{
        // type -->  0 : 애니메이션 없음  1 : 체크메이트   2 : 스테일메이트
        int type = 0;

        if (PhotonNetwork.room.maxPlayers == 2)
             type = GameManager.Instance().CheckState();

        //Debug.Log("0 : 애니메이션 없음  1 : 체크  2 : 체크메이트   3 : 스테일메이트 // 현재상태 :  " + type);

        //마이턴애니메이션
        StartCoroutine(TurnAnimationStart(type));
	}

	[PunRPC]
    void ShowAnimationOther(int type)
    {
        switch(type)
        {
            case 0:
                break;
            case 1:
                StartCoroutine(GameManager.Instance().CheckAnimation());
                break;
            case 2:
                StartCoroutine(GameManager.Instance().CheckmateAnimation(true));
                break;
            case 3:
                StartCoroutine(GameManager.Instance().StalemateAnimation());
                break;
        }
    }

    IEnumerator TurnAnimationStart(int type)
    {
        switch (type)
        {
            case 0:
                yield return new WaitForSeconds(0.1f);
                StartCoroutine(TurnAnimation());
                break;
            case 1:
                yield return new WaitForSeconds(0.1f);

                if(PhotonNetwork.room.maxPlayers == 2)
                    pv.RPC("ShowAnimationOther", PhotonTargets.Others, type);

                yield return GameManager.Instance().CheckAnimation();
                yield return new WaitForSeconds(0.2f);
                StartCoroutine(TurnAnimation());
                break;
            case 2:
                yield return new WaitForSeconds(0.1f);

                if (PhotonNetwork.room.maxPlayers == 2)
                    pv.RPC("ShowAnimationOther", PhotonTargets.Others, type);
                yield return GameManager.Instance().CheckmateAnimation(false);
                break;
            case 3:
                yield return new WaitForSeconds(0.1f);

                if (PhotonNetwork.room.maxPlayers == 2)
                    pv.RPC("ShowAnimationOther", PhotonTargets.Others, type);
                yield return GameManager.Instance().StalemateAnimation();
                break;
        }

        yield return true;
    }

	IEnumerator TurnAnimation()
	{
		turntext.text = "MyTrun";

		Vector3 imgScale = turnImg.transform.localScale;
		imgScale.y = 3.0f;
		turnImg.transform.localScale = imgScale;
		for (int i = 0; i < 20; i++)
		{
			imgScale.y -= 0.1f;
			turnImg.transform.localScale = imgScale;
			yield return new WaitForEndOfFrame();
		}

		yield return new WaitForSeconds(0.8f);

		for (int i = 0; i < 10; i++)
		{
			imgScale.y -= 0.1f;
			turnImg.transform.localScale = imgScale;
			yield return new WaitForEndOfFrame();
		}

		stop = false;

		yield return true;
	}

	[PunRPC]
	void SecendPlayerLogin()
	{
		GameManager.Instance ().FindPlayer ();
	}

	public IEnumerator selectPromotion(string color)
	{
		if (color == playerColor) {
            yield return PromotionWindowOpen();

        }
		yield return selectPromotionType(color);
	}

	IEnumerator selectPromotionType(string color)
	{
		while (selectPromotionTypeNum == 0) {
			yield return new WaitForEndOfFrame ();
		}

		if (color == playerColor) {
			GameManager.Instance ().selectPromotionType = selectPromotionTypeNum;
            yield return PromotionWindowClose();
        }
		yield return new WaitForSeconds (0.5f);
		//Debug.Log ("셀렉트 초기화");
		selectPromotionTypeNum = 0;
		yield return true;
	}

	[PunRPC]
	void setEnemyPromotion(string enemySelectPromotionTypeNum)
	{
		GameManager.Instance ().selectPromotionType = int.Parse (enemySelectPromotionTypeNum);
		selectPromotionTypeNum = int.Parse(enemySelectPromotionTypeNum);
		//GameManager.Instance ().endPromotion = true;
		//Debug.Log ("selectPromotionTypeNum" + selectPromotionTypeNum);
	}

    [PunRPC]
    void initMoveAble()
    {
        GameManager.Instance().whiteMoveAble = false;
        GameManager.Instance().blackMoveAble = false;

        //Debug.Log("초기화");
    }

    public IEnumerator PromotionWindowOpen()
    {
        Vector3 promotionWindowScale = promotionWindow.transform.localScale;
        for(int i = 0; i < 10; i++)
        {
            promotionWindowScale.y += 0.1f;
            promotionWindow.transform.localScale = promotionWindowScale;
            yield return new WaitForEndOfFrame();
        }

        yield return true;
    }

    public IEnumerator PromotionWindowClose()
    {
        Vector3 promotionWindowScale = promotionWindow.transform.localScale;
        for (int i = 0; i < 10; i++)
        {
            promotionWindowScale.y -= 0.1f;
            promotionWindow.transform.localScale = promotionWindowScale;
            yield return new WaitForEndOfFrame();
        }
        yield return true;
    }

    public void PromotionQueen()
    {
        selectPromotionTypeNum = 1;
        pv.RPC("setEnemyPromotion", PhotonTargets.Others, selectPromotionTypeNum.ToString());
    }

    public void PromotionRook()
    {
        selectPromotionTypeNum = 2;
        pv.RPC("setEnemyPromotion", PhotonTargets.Others, selectPromotionTypeNum.ToString());
    }

    public void PromotionBishop()
    {
        selectPromotionTypeNum = 3;
        pv.RPC("setEnemyPromotion", PhotonTargets.Others, selectPromotionTypeNum.ToString());
    }

    public void PromotionKnight()
    {
        selectPromotionTypeNum = 4;
        pv.RPC("setEnemyPromotion", PhotonTargets.Others, selectPromotionTypeNum.ToString());
    }

}
