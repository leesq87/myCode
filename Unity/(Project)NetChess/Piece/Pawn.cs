using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Pawn : Movement
{

    private int[] currentPosition;

    public bool isFirstMove;
    public bool isDoubleMove;

    void Awake()
    {
        moveAble = new List<index>();
        isFirstMove = true;
        isDoubleMove = false;
		SetPosition ();
    }

    void Update () {
	
	}

	void SetPosition()
	{
		currentPosition = GetPosition ();
	}

    /// <summary>
    /// 해당 칸에 적이 있는지 체크
    /// </summary>
    /// <param name="targetPosition">해당 칸 인덱스</param>
    /// <param name="type">공격하면서 체크인지 앞으로 체크인지 구분</param>
    /// <param name="delta">인덱스 변화 값</param>
    void EnemyCheck(int [] targetPosition, int type, int delta)
    {
        GameObject targetPosObj = GameObject.Find(ConvertPosition(targetPosition));

        

        //------------ 적을 공격하면서 이동 가능 경로 검사 ---------- 
        if (type == 0)
        {
            if (targetPosObj.transform.childCount > 0)
            {
                // 레이어 비교
                if (gameObject.layer != targetPosObj.transform.GetChild(0).gameObject.layer)
                {
                    moveAbleAdd(targetPosition);
                }
            }
        }
        //----------- 앞으로 이동 가능 경로 검사 ---------------
        else
        {
            // 해당 칸에 기물이 존재하면 리턴
            if (targetPosObj.transform.childCount > 0)
            {
                return;             
            }
            else
            {
                moveAbleAdd(targetPosition);

                // 처음 이동이라면 2번째 칸 체크
                if (isFirstMove)
                {
                    targetPosition[0] = currentPosition[0];
                    targetPosition[1] = currentPosition[1] + delta;

                    if (targetPosition[0] > 7 || targetPosition[1] > 7 || targetPosition[0] < 0 || targetPosition[1] < 0)
                    {
                        return;
                    }

                   

                    GameObject targetPosObj2 = GameObject.Find(ConvertPosition(targetPosition));

                    // 2번째 칸에 자식이 있으면 리턴
                    if (targetPosObj2.transform.childCount > 0)
                    {
                        return;
                    }
                    // 없으면 이동가능 경로에 추가
                    else
                    {
                        moveAbleAdd(targetPosition);
                    }
                }
            }
        }
    }

    void EnPassantCheck(int delta)
    {
        int[] targetPosition = new int[2];

        for (int i = 0; i < 2; i++)
        {
            switch (i)
            {
                case 0:
                    // 좌
                    targetPosition[0] = currentPosition[0] - 1;
                    targetPosition[1] = currentPosition[1];
                    break;
                case 1:
                    // 우
                    targetPosition[0] = currentPosition[0] + 1;
                    targetPosition[1] = currentPosition[1];
                    break;
            }
            // 보드를 벗어나면 리턴
            if (targetPosition[0] > 7 || targetPosition[1] > 7 || targetPosition[0] < 0 || targetPosition[1] < 0)
            {
                continue;
            }

            // 옆 칸 
            GameObject target = GameObject.Find(ConvertPosition(targetPosition));
            // 옆 칸의 기물이 있으면
            if( target.transform.childCount > 0 )
            {

                Pawn targetPawn = target.transform.GetChild(0).GetComponent<Pawn>();
                // 기물이 적팀 폰이였을때
            //    Debug.Log(target.layer + "/" + target.transform.GetChild(0).gameObject.layer);
                if(targetPawn && target.transform.GetChild(0).gameObject.layer != gameObject.layer)
                {
                    // 옆 칸의 폰이 2칸 움직였을 때 앙파상 가능
                    if(targetPawn.isDoubleMove)
                    {
                        targetPosition[0] = targetPosition[0];
                        targetPosition[1] = targetPosition[1] + delta;
                        Debug.Log(ConvertPosition(targetPosition));
                        moveAbleAdd(targetPosition);
                    }
                }
                // 기물이 폰이 아님
                else
                {
                   // Debug.Log("옆에 폰 없슴");
                }
            }
            // 기물이 없으면
            else
            {
               // Debug.Log("폰 옆에 암것도 없다");
            }
        }
    }

    /// <summary>
    /// 폰의 움직임 대각선방향 데드존 설정
    /// </summary>
    public override void PieceMovement()
	{
		moveAble.Clear();
		currentPosition = GetPosition();

        // 화이트일때
        if (gameObject.layer == 9)
        {
            // 양쪽 대각선에 적이 있는지 체크
            int[] targetPosition = new int[2];

            for (int i = 0; i < 2; i++)
            {
                switch (i)
                {
                    case 0:
                        // 상좌
                        targetPosition[0] = currentPosition[0] - 1;
                        targetPosition[1] = currentPosition[1] + 1;
                        break;
                    case 1:
                        // 상우
                        targetPosition[0] = currentPosition[0] + 1;
                        targetPosition[1] = currentPosition[1] + 1;                    
                        break;
                }
                // 보드를 벗어나면 리턴
                if (targetPosition[0] > 7 || targetPosition[1] > 7 || targetPosition[0] < 0 || targetPosition[1] < 0)
                {
                    continue;
                }
                //------------ 이동 가능 경로 검사 ----------
                EnemyCheck(targetPosition, 0, 2);
            }
            // 앞으로 이동 가능 경로 검사
            targetPosition[0] = currentPosition[0];
            targetPosition[1] = currentPosition[1] + 1;

            if (targetPosition[0] > 7 || targetPosition[1] > 7 || targetPosition[0] < 0 || targetPosition[1] < 0)
            {
                return;
            }
            EnemyCheck(targetPosition, 1, 2);

            // 앙파상 체크
            EnPassantCheck(1);

        }
        // 블랙일때
        else
        {
            // 양쪽 대각선에 적이 있는지 체크
            int[] targetPosition = new int[2];

            for (int i = 0; i < 2; i++)
            {
                switch (i)
                {
                    case 0:
                        // 하좌
                        targetPosition[0] = currentPosition[0] - 1;
                        targetPosition[1] = currentPosition[1] - 1;
                        break;
                    case 1:
                        // 하우
                        targetPosition[0] = currentPosition[0] + 1;
                        targetPosition[1] = currentPosition[1] - 1;
                        break;
                }
                // 보드를 벗어나면 리턴
                if (targetPosition[0] > 7 || targetPosition[1] > 7 || targetPosition[0] < 0 || targetPosition[1] < 0)
                {
                    continue;
                }
                //------------ 이동 가능 경로 검사 ----------
                EnemyCheck(targetPosition, 0, -2);
            }
            // 앞으로 이동 가능 경로 검사
            targetPosition[0] = currentPosition[0];
            targetPosition[1] = currentPosition[1] - 1;

            if (targetPosition[0] > 7 || targetPosition[1] > 7 || targetPosition[0] < 0 || targetPosition[1] < 0)
            {
                return;
            }
            EnemyCheck(targetPosition, 1 , -2);

            EnPassantCheck(-1);
        }      
    }

    public override void OnlyCheckDeadZone()
    {
        int[] checkPosition = GetPosition();

        // 화이트일때
        if (gameObject.layer == 9)
        {
            // 양쪽 대각선에 적이 있는지 체크
            int[] targetPosition = new int[2];

            for (int i = 0; i < 2; i++)
            {
                switch (i)
                {
                    case 0:
                        // 상좌
                        targetPosition[0] = checkPosition[0] - 1;
                        targetPosition[1] = checkPosition[1] + 1;
                        break;
                    case 1:
                        // 상우
                        targetPosition[0] = checkPosition[0] + 1;
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
                targetPosObj.GetComponent<PiecePosition>().blackDead = true;

            }
        }
        // 블랙일때
        else
        {
            // 양쪽 대각선에 적이 있는지 체크
            int[] targetPosition = new int[2];

            for (int i = 0; i < 2; i++)
            {
                switch (i)
                {
                    case 0:
                        // 하좌
                        targetPosition[0] = checkPosition[0] - 1;
                        targetPosition[1] = checkPosition[1] - 1;
                        break;
                    case 1:
                        // 하우
                        targetPosition[0] = checkPosition[0] + 1;
                        targetPosition[1] = checkPosition[1] - 1;
                        break;
                }
                // 보드를 벗어나면 리턴
                if (targetPosition[0] > 7 || targetPosition[1] > 7 || targetPosition[0] < 0 || targetPosition[1] < 0)
                {
                    continue;
                }

                // 데드존 세트
                GameObject targetPosObj = GameObject.Find(ConvertPosition(targetPosition));
                targetPosObj.GetComponent<PiecePosition>().whiteDead = true;
            }
        }
    }

    public void NextTurn()
    {
        isDoubleMove = false;
    }
}            
