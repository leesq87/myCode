using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class King : Movement
{

    private int[] currentPosition;

    public bool isFirstMove;

    void Awake()
    {
        moveAble = new List<index>();
        isFirstMove = true;
		SetPosition ();
    }

    void Update()
    {


    }
	void SetPosition()
	{
		currentPosition = GetPosition ();
	}

    void CastlingCheck()
    {
        int[] targetPosition = new int[2];

        targetPosition[0] = currentPosition[0] - 1;
        targetPosition[1] = currentPosition[1];

        _CastlingCheck(targetPosition, -1); //좌

        targetPosition[0] = currentPosition[0] + 1;
        targetPosition[1] = currentPosition[1];

        _CastlingCheck(targetPosition, 1);  // 우
    }

    void _CastlingCheck(int [] targetPosition, int delta)
    {

        // 보드를 벗어나면 리턴
        if (targetPosition[0] > 7 || targetPosition[1] > 7 || targetPosition[0] < 0 || targetPosition[1] < 0)
        {
            return;
        }
        GameObject targetPosObj = GameObject.Find(ConvertPosition(targetPosition));

        // 블랙일때
        if (gameObject.layer == 10)
        {
            // 데드존이면 리턴
            if(targetPosObj.GetComponent<PiecePosition>().blackDead)
            {
                return;
            }
            else
            {
                // 기물이 있을경우
                if (targetPosObj.transform.childCount > 0)
                {
                  //  Debug.Log(targetPosObj.transform.GetChild(0).name);
                    // 룩이면 룩이 움직였는지 검사
                    if(targetPosObj.transform.GetChild(0).GetComponent<Rook>())
                    {
                        // 룩이 움직였으면 리턴
                        if(!targetPosObj.transform.GetChild(0).GetComponent<Rook>().isFirstMove)
                        {
                            return;
                        }
                        // 캐슬링 가능
                        else
                        {
                            // 킹 사이드 캐슬링
                            if(delta > 0 )
                            {
                                targetPosition[0] = currentPosition[0] + 2;
                                targetPosition[1] = currentPosition[1];
                            }
                            // 퀸 사이드 캐슬링
                            else
                            {
                                targetPosition[0] = currentPosition[0] - 2;
                                targetPosition[1] = currentPosition[1];
                            }
                            moveAbleAdd(targetPosition);
                            return;
                        }
                    }
                    // 룩이 아니면 리턴
                    else
                    {
                        return;
                    }
                }
                // 없을 경우 다음 칸 검사
                else
                {
                    targetPosition[0] = targetPosition[0] + delta;
                    _CastlingCheck(targetPosition, delta);
                }
            }
        }
        // 화이트일경우
        else
        {
            // 데드존이면 리턴
            if (targetPosObj.GetComponent<PiecePosition>().whiteDead)
            {
                return;
            }
            else
            {
                // 기물이 있을경우
                if (targetPosObj.transform.childCount > 0)
                {
                    // 룩이면 룩이 움직였는지 검사
                    if (targetPosObj.transform.GetChild(0).GetComponent<Rook>())
                    {
                        // 룩이 움직였으면 리턴
                        if (!targetPosObj.transform.GetChild(0).GetComponent<Rook>().isFirstMove)
                        {
                            return;
                        }
                        // 캐슬링 가능
                        else
                        {
                            // 킹 사이드 캐슬링
                            if (delta > 0)
                            {
                                targetPosition[0] = currentPosition[0] + 2;
                                targetPosition[1] = currentPosition[1];
                            }
                            // 퀸 사이드 캐슬링
                            else
                            {
                                targetPosition[0] = currentPosition[0] - 2;
                                targetPosition[1] = currentPosition[1];
                            }
                            moveAbleAdd(targetPosition);
                            Debug.Log("캐슬링가능");
                            return;
                        }
                    }
                    // 룩이 아니면 리턴
                    else
                    {
                        return;
                    }
                }
                // 없을 경우 다음 칸 검사
                else
                {
                    targetPosition[0] = targetPosition[0] + delta;
                    _CastlingCheck(targetPosition, delta);
                }
            }
        }
    }

    /// <summary>
    /// 킹 움직임
    /// 여덟 칸 체크
    /// </summary>
    public override void PieceMovement()
	{
		moveAble.Clear();
		currentPosition = GetPosition();
        // 이동할 칸 인덱스 저장
        int[] targetPosition = new int[2];

        for (int i = 0; i < 8; i++)
        {
            switch (i)
            {
                case 0: // 우상
                    targetPosition[0] = currentPosition[0] + 1;
                    targetPosition[1] = currentPosition[1] + 1;
                    break;
                case 1: // 우
                    targetPosition[0] = currentPosition[0] + 1;
                    targetPosition[1] = currentPosition[1];
                    break;
                case 2: // 우하
                    targetPosition[0] = currentPosition[0] + 1;
                    targetPosition[1] = currentPosition[1] - 1;
                    break;
                case 3: // 하
                    targetPosition[0] = currentPosition[0];
                    targetPosition[1] = currentPosition[1] - 1;
                    break;
                case 4: // 좌하
                    targetPosition[0] = currentPosition[0] - 1;
                    targetPosition[1] = currentPosition[1] - 1;
                    break;
                case 5: // 좌
                    targetPosition[0] = currentPosition[0] - 1;
                    targetPosition[1] = currentPosition[1];
                    break;
                case 6: // 좌상
                    targetPosition[0] = currentPosition[0] - 1;
                    targetPosition[1] = currentPosition[1] + 1;
                    break;
                case 7: // 상
                    targetPosition[0] = currentPosition[0];
                    targetPosition[1] = currentPosition[1] + 1;
                    break;
            }
            // 보드를 벗어나면 리턴
            if (targetPosition[0] > 7 || targetPosition[1] > 7 || targetPosition[0] < 0 || targetPosition[1] < 0)
            {
                continue;
            }


            // 데드존 세트
            GameObject targetPosObj = GameObject.Find(ConvertPosition(targetPosition));

            //------------ 이동 가능 경로 검사 ----------
           
            // 해당 칸에 기물이 있으면
            if (targetPosObj.transform.childCount > 0)
            {
                // 레이어 비교( 상대팀 기물이면 이동가능한 경로에 추가 ) 
               // Debug.Log(gameObject.name + "______" + gameObject.layer + " // " + targetPosObj.transform.GetChild(0).gameObject.layer);
               // Debug.Log(ConvertPosition(targetPosition)+"/"+targetPosObj.transform.GetChild(0).gameObject.name);
                if (gameObject.layer != targetPosObj.transform.GetChild(0).gameObject.layer)
                {
                    //Debug.Log(gameObject.name+"기물이 상대편이다");
                    moveAbleAdd(targetPosition);
                }
                else
                {
                   // Debug.Log(gameObject.name +  "우리팀 기물");
                }
            }
            // 해당 칸에 기물이 없으면
            else
            {
               // Debug.Log(gameObject.name + " 아무것도없다");
                moveAbleAdd(targetPosition);
            }
        }
        // 킹을 한 번도 안움직였을때만 캐슬링 체크
        if (isFirstMove)
        {
            CastlingCheck();
        }
    }


    public override void OnlyCheckDeadZone()
    {
        int[] checkPosition = GetPosition();
        // 이동할 칸 인덱스 저장
        int[] targetPosition = new int[2];

        for (int i = 0; i < 8; i++)
        {
            switch (i)
            {
                case 0: // 우상
                    targetPosition[0] = checkPosition[0] + 1;
                    targetPosition[1] = checkPosition[1] + 1;
                    break;
                case 1: // 우
                    targetPosition[0] = checkPosition[0] + 1;
                    targetPosition[1] = checkPosition[1];
                    break;
                case 2: // 우하
                    targetPosition[0] = checkPosition[0] + 1;
                    targetPosition[1] = checkPosition[1] - 1;
                    break;
                case 3: // 하
                    targetPosition[0] = checkPosition[0];
                    targetPosition[1] = checkPosition[1] - 1;
                    break;
                case 4: // 좌하
                    targetPosition[0] = checkPosition[0] - 1;
                    targetPosition[1] = checkPosition[1] - 1;
                    break;
                case 5: // 좌
                    targetPosition[0] = checkPosition[0] - 1;
                    targetPosition[1] = checkPosition[1];
                    break;
                case 6: // 좌상
                    targetPosition[0] = checkPosition[0] - 1;
                    targetPosition[1] = checkPosition[1] + 1;
                    break;
                case 7: // 상
                    targetPosition[0] = checkPosition[0];
                    targetPosition[1] = checkPosition[1] + 1;
                    break;
            }
            // 보드를 벗어나면 리턴
            if (targetPosition[0] > 7 || targetPosition[1] > 7 || targetPosition[0] < 0 || targetPosition[1] < 0)
            {
                continue;
            }


            // 데드존 세트
            GameObject targetPosObj = GameObject.Find(ConvertPosition(targetPosition));
            if (gameObject.layer == 10)
            {
                targetPosObj.GetComponent<PiecePosition>().whiteDead = true;
            }
            else
            {
                targetPosObj.GetComponent<PiecePosition>().blackDead = true;
            }
        }
    }
}
