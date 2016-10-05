using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Knight : Movement
{

    private int[] currentPosition;

    void Awake()
    {
        moveAble = new List<index>();
		SetPosition ();
    }

	void Update () {

        
	}
	void SetPosition()
	{
		currentPosition = GetPosition ();
	}
    /// <summary>
    /// 나이트 움직임
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
            switch(i)
            {
                case 0: // 우상
                    targetPosition[0] = currentPosition[0] + 2;
                    targetPosition[1] = currentPosition[1] + 1;
                    break;
                case 1: // 우하
                    targetPosition[0] = currentPosition[0] + 2;
                    targetPosition[1] = currentPosition[1] - 1;
                    break;
                case 2: // 좌상
                    targetPosition[0] = currentPosition[0] - 2;
                    targetPosition[1] = currentPosition[1] + 1;
                    break;
                case 3: // 좌하
                    targetPosition[0] = currentPosition[0] - 2;
                    targetPosition[1] = currentPosition[1] - 1;
                    break;
                case 4: // 상좌
                    targetPosition[0] = currentPosition[0] - 1;
                    targetPosition[1] = currentPosition[1] + 2;
                    break;
                case 5: // 상우
                    targetPosition[0] = currentPosition[0] + 1;
                    targetPosition[1] = currentPosition[1] + 2;
                    break;
                case 6: // 하좌
                    targetPosition[0] = currentPosition[0] - 1;
                    targetPosition[1] = currentPosition[1] - 2;
                    break;
                case 7: // 하우
                    targetPosition[0] = currentPosition[0] + 1;
                    targetPosition[1] = currentPosition[1] - 2;
                    break;
            }
            // 보드를 벗어나면 리턴
            if (targetPosition[0] > 7 || targetPosition[1] > 7 || targetPosition[0] < 0 || targetPosition[1] < 0)
            {
               // Debug.Log("컨트뉴");
                continue;
            }
            
            // 데드존 세트
            GameObject targetPosObj = GameObject.Find(ConvertPosition(targetPosition));
            //------------ 이동 가능 경로 검사 ----------
            
            // 해당 칸에 기물이 있으면
            if (targetPosObj.transform.childCount > 0)
            {
                // 레이어 비교( 상대팀 기물이면 이동가능한 경로에 추가 ) 
                if (gameObject.layer != targetPosObj.transform.GetChild(0).gameObject.layer)
                {
                    //Debug.Log("나이트 : 기물이 상대편이다");
                    moveAbleAdd(targetPosition);
                }
                else
                {
                    //Debug.Log("나이트 : 우리팀 기물");
                }
            }
            // 해당 칸에 기물이 없으면
            else
            {
                //Debug.Log("나이트 : 아무것도없다");
                moveAbleAdd(targetPosition);
            }
        }
        //Debug.Log("나이트 : 이동가능경로 : " + moveAble.Count);

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
                    targetPosition[0] = checkPosition[0] + 2;
                    targetPosition[1] = checkPosition[1] + 1;
                    break;
                case 1: // 우하
                    targetPosition[0] = checkPosition[0] + 2;
                    targetPosition[1] = checkPosition[1] - 1;
                    break;
                case 2: // 좌상
                    targetPosition[0] = checkPosition[0] - 2;
                    targetPosition[1] = checkPosition[1] + 1;
                    break;
                case 3: // 좌하
                    targetPosition[0] = checkPosition[0] - 2;
                    targetPosition[1] = checkPosition[1] - 1;
                    break;
                case 4: // 상좌
                    targetPosition[0] = checkPosition[0] - 1;
                    targetPosition[1] = checkPosition[1] + 2;
                    break;
                case 5: // 상우
                    targetPosition[0] = checkPosition[0] + 1;
                    targetPosition[1] = checkPosition[1] + 2;
                    break;
                case 6: // 하좌
                    targetPosition[0] = checkPosition[0] - 1;
                    targetPosition[1] = checkPosition[1] - 2;
                    break;
                case 7: // 하우
                    targetPosition[0] = checkPosition[0] + 1;
                    targetPosition[1] = checkPosition[1] - 2;
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
