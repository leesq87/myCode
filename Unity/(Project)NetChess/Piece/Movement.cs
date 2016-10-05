using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;

public class Movement : MonoBehaviour {

    public List<index> moveAble;

    public struct index
    {
        public int rank;
        public int file;

        public index(int p1, int p2)
        {
            rank = p1;
            file = p2;
        }
    }
    /// <summary>
    /// 현재 랭크(행)와 파일(열)을 받는 함수
    /// <para>
    /// 재정의 없이 사용
    /// </para>
    /// <returns>
    /// returnValue[0] = 0 ~ 7 (A ~ H)
    /// returnValue[1] = 0 ~ 7 (1 ~ 8)
    /// </returns>
    /// </summary>
    public int[] GetPosition()
    {
        if(transform.parent == null)
        {
            int[] _pos = new int[2];
            return _pos;
        }
        int[] pos = new int[2];

        string str = transform.parent.name;

        pos[0] = (str[0] - 'A');
        pos[1] = (str[1] - '1');
        
        return pos;
    }

    /// <summary>
    /// 문자열을 인자로 넘기면
    /// 현재 랭크(행)와 파일(열)을 받는 함수
    /// 오버로딩
    /// </summary>
    /// <param name="str">칸 이름</param>
    /// <returns></returns>
    public int[] GetPosition(string str)
    {
        int[] pos = new int[2];

        pos[0] = (str[0] - 'A');
        pos[1] = (str[1] - '1');

        return pos;
    }

    /// <summary>
    /// 기물들의 움직임 제어 함수
    /// <para>
    /// 기물마다 재정의해서 사용
    /// </para>
    /// </summary>
    public virtual void PieceMovement() { }
    public virtual void OnlyCheckDeadZone() { }

    /// <summary>
    /// 각 기물이 가지고 있는 이동 가능한 경로 표시 on 함수
    /// </summary>
    public void ShowMoveAbleOn()
    {
        for(int i= 0; i < moveAble.Count; i++)
        {
            index idx = moveAble[i];
            int[] pos = new int[2];
            pos[0] = idx.rank;
            pos[1] = idx.file;
            GameObject.Find(ConvertPosition(pos)).GetComponent<SpriteRenderer>().enabled = true;
        }
    }

    /// <summary>
    /// 이동 가능한 경로 표시 off 함수
    /// </summary>
    public void ShowMoveAbleOff()
    {
        for (int i = 0; i < moveAble.Count; i++)
        {
            index idx = moveAble[i];
            int[] pos = new int[2];
            pos[0] = idx.rank;
            pos[1] = idx.file;
            GameObject.Find(ConvertPosition(pos)).GetComponent<SpriteRenderer>().enabled = false;
        }
    }

    /// <summary>
    /// int형 위치값을 넣으면 String으로 변환 함수
    /// </summary>
    /// <param name="Pos">
    /// int형 위치값
    /// </param>
    /// <returns>
    /// 변환된 위치명
    /// </returns>
    public string ConvertPosition(int[] Pos)
    {
        char[] convertPos = new char[2];

        convertPos[0] = Convert.ToChar(('A' + Pos[0]));
        convertPos[1] = Convert.ToChar(('1' + Pos[1]));

        string str = new string(convertPos);
        return str;
    }
    /// <summary>
    /// 이동가능 경로 표시
    /// 재귀함수 호출 중 기물을 만났을 때
    /// 같은 레이어가 아니면 이동가능 경로 표시 후 리턴 
    /// </summary>
    /// <param name="targetPosition">
    /// 보드에서 타겟 인덱스
    /// </param>
    public bool SetDeadZone(int[] targetPosition)
    {
        GameObject targetPosObj = GameObject.Find(ConvertPosition(targetPosition));
        if (gameObject.layer == 10)
        {
            if (targetPosObj.transform.childCount > 0)
            {
                // 레이어 비교
                if (gameObject.layer != targetPosObj.transform.GetChild(0).gameObject.layer)
                {
                    moveAbleAdd(targetPosition);
                }
                return true;
            }
        }
        else
        {
            if (targetPosObj.transform.childCount > 0)
            {
                // 레이어 비교
                if (gameObject.layer != targetPosObj.transform.GetChild(0).gameObject.layer)
                {                    
                    moveAbleAdd(targetPosition);
                }
                return true;
            }
        }
        moveAbleAdd(targetPosition);   
        return false;
    }

    /// <summary>
    /// 이동가능 경로 확인 중 경로로 옮겼다고 가정하고 데드존 세트
    /// </summary>
    /// <param name="targetPosition">칸의 인덱스</param>
    /// <returns></returns>
    public bool OnlyCheckDeadZone(int[] targetPosition)
    {
        GameObject targetPosObj = GameObject.Find(ConvertPosition(targetPosition));
        if (gameObject.layer == 10)
        {
            targetPosObj.GetComponent<PiecePosition>().whiteDead = true;
            if (targetPosObj.transform.childCount > 0)
            {
                return true;
            }
            //Debug.Log("셋하는놈: " + gameObject.name + "   데드존 셋 : " + GameObject.Find(ConvertPosition(targetPosition)));
        }
        else
        {
            targetPosObj.GetComponent<PiecePosition>().blackDead = true;
            if (targetPosObj.transform.childCount > 0)
            {
                return true;
            }
        }
        return false;
    }

    /// <summary>
    /// 호출한 스크립트 리스트에
    /// 현재 좌표 추가
    /// </summary>
    /// <param name="Pos">칸의 인덱스</param>
    public void moveAbleAdd(int[] Pos)
    {
        index idx = new index(Pos[0], Pos[1]);
       
            //현재 위치 부모이름 저장
            Transform originalPos = transform.parent;

            // 검사하는 칸의 위치
            string movePosName = ConvertPosition(Pos);
            Transform movePos = GameObject.Find(movePosName).transform;
            Transform tmpSpace = GameObject.Find("TmpSpace").transform;

            // 검사하는 칸에 적이 있으면 임시공간으로 옮김
            if (movePos.childCount > 0)
            {
                if (movePos.GetChild(0).gameObject.layer != transform.gameObject.layer)
                {
                    movePos.GetChild(0).parent = tmpSpace.transform;
                }
            }
            // 내가 움직이는 기물 검사하는 칸으로 이동
            transform.parent = movePos.transform;

            // 브로드캐스트 호출
            // 옮겼다고 가정하고 데드존 재설정
            GameObject.Find("PiecePosition").BroadcastMessage("ResetDeadZone");
            GameObject.Find("PiecePosition").BroadcastMessage("OnlyCheckDeadZone");
            // 왕이 체크인지 체크
            if (gameObject.layer == 10)
            {
                string blackKing = GameObject.FindWithTag("BlackKing").transform.parent.name;

                if (!GameObject.Find(blackKing).GetComponent<PiecePosition>().blackDead)
                {
                // 왕이 체크가 아니면 이동 가능 경로에 추가
                    moveAbleIdx(idx);

                //Debug.Log("블랙에드");
                GameManager.Instance().blackMoveAble = true;
                }
            }
            else
            {
                string whiteKing = GameObject.FindWithTag("WhiteKing").transform.parent.name;
                if (!GameObject.Find(whiteKing).GetComponent<PiecePosition>().whiteDead)
                {
                // 왕이 체크가 아니면 이동 가능 경로에 추가
              //  Debug.Log(transform.parent.name + "/" + transform.name + " => " + ConvertPosition(Pos)+"추가");
                    moveAbleIdx(idx);

                //Debug.Log("화이트에드");
                    GameManager.Instance().whiteMoveAble = true;
                }
         //   Debug.Log(transform.parent.name + "/" + transform.name + " => " + ConvertPosition(Pos)+"체크상태라서 추가 못함");
            }
            // 위치 원상 복구
            transform.parent = originalPos.transform;
            if (tmpSpace.childCount > 0)
            {
                tmpSpace.GetChild(0).parent = movePos;
            }

            // 데드존 원상태로 복구
            GameObject.Find("PiecePosition").BroadcastMessage("ResetDeadZone");
            GameObject.Find("PiecePosition").BroadcastMessage("OnlyCheckDeadZone");      
    }

    /// <summary>
    /// 해당 기물의 이동가능 경로를 저장
    /// </summary>
    /// <param name="idx">칸의 인덱스</param>
    void moveAbleIdx(index idx)
    {
        if (gameObject.GetComponent<Pawn>())
        {
            gameObject.GetComponent<Pawn>().moveAble.Add(idx);
        }
        if (gameObject.GetComponent<Knight>())
        {
            gameObject.GetComponent<Knight>().moveAble.Add(idx);
        }
        if (gameObject.GetComponent<Bishop>())
        {
            gameObject.GetComponent<Bishop>().moveAble.Add(idx);
        }
        if (gameObject.GetComponent<Rook>())
        {
            gameObject.GetComponent<Rook>().moveAble.Add(idx);
        }
        if (gameObject.GetComponent<Queen>())
        {
            gameObject.GetComponent<Queen>().moveAble.Add(idx);
        }
        if (gameObject.GetComponent<King>())
        {
            gameObject.GetComponent<King>().moveAble.Add(idx);
        }
    }
}
