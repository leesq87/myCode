using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Queen : Movement
{

    private int[] currentPosition;

    void Awake()
    {
        moveAble = new List<index>();
		SetPosition();
    }

    void Update()
    {
		
    }
	void SetPosition()
	{
		currentPosition = GetPosition ();
	}
    /// <summary>
    /// 퀸이 일직선/ 대각선 으로 이동가능한 칸 체크.
    /// 여덟 방향으로 각각 재귀함수 호출 
    /// </summary>
    public override void PieceMovement()
	{
		moveAble.Clear();
		currentPosition = GetPosition();
        // 일직선
        _PieceMovement(currentPosition[0] + 1, currentPosition[1], 1, 0); // 우 방향
        _PieceMovement(currentPosition[0] - 1, currentPosition[1], -1, 0); // 좌 방향
        _PieceMovement(currentPosition[0], currentPosition[1] - 1, 0, -1); // 하 방향
        _PieceMovement(currentPosition[0], currentPosition[1] + 1, 0, 1);// 상 방향

        // 대각선
        _PieceMovement(currentPosition[0] + 1, currentPosition[1] + 1, 1, 1); // 우상 방향
        _PieceMovement(currentPosition[0] + 1, currentPosition[1] - 1, 1, -1); // 우하 방향
        _PieceMovement(currentPosition[0] - 1, currentPosition[1] + 1, -1, 1); // 좌상 방향
        _PieceMovement(currentPosition[0] - 1, currentPosition[1] - 1, -1, -1);// 좌하 방향
        
    }
    /// <summary>
    /// 해당 방향으로 한 칸씩 검사하며 재귀호출
    /// </summary>
    /// <param name="rank"> 보드의 열 (A,B,C...) 인덱스</param>
    /// <param name="file"> 보드의 행 (1,2,3...) 인덱스</param>
    /// <param name="rankDelta"> 열 증감값</param>
    /// <param name="fileDelta"> 행 증감값</param>
    public void _PieceMovement(int rank, int file, int rankDelta, int fileDelta)
    {
        // 보드를 벗어나면 리턴
        if (rank < 0 || rank > 7 || file < 0 || file > 7)
            return;

        // 이동가능 칸 인덱스 저장
        int[] targetPosition = new int[2];
        targetPosition[0] = rank;
        targetPosition[1] = file;

        // 데드존 세트
        if (SetDeadZone(targetPosition))
            return;

        _PieceMovement(rank + rankDelta, file + fileDelta, rankDelta, fileDelta);
    }

    public override void OnlyCheckDeadZone()
    {
        int[] checkPosition = GetPosition();
  
        _OnlyCheckDeadZone(checkPosition[0] + 1, checkPosition[1], 1, 0); // 우 방향
        _OnlyCheckDeadZone(checkPosition[0] - 1, checkPosition[1], -1, 0); // 좌 방향
        _OnlyCheckDeadZone(checkPosition[0], checkPosition[1] - 1, 0, -1); // 하 방향
        _OnlyCheckDeadZone(checkPosition[0], checkPosition[1] + 1, 0, 1);// 상 방향

        // 대각선
        _OnlyCheckDeadZone(checkPosition[0] + 1, checkPosition[1] + 1, 1, 1); // 우상 방향
        _OnlyCheckDeadZone(checkPosition[0] + 1, checkPosition[1] - 1, 1, -1); // 우하 방향
        _OnlyCheckDeadZone(checkPosition[0] - 1, checkPosition[1] + 1, -1, 1); // 좌상 방향
        _OnlyCheckDeadZone(checkPosition[0] - 1, checkPosition[1] - 1, -1, -1);// 좌하 방향
    }

    public void _OnlyCheckDeadZone(int rank, int file, int rankDelta, int fileDelta)
    {
        // 보드를 벗어나면 리턴
        if (rank < 0 || rank > 7 || file < 0 || file > 7)
            return;

        // 이동가능 칸 인덱스 저장
        int[] targetPosition = new int[2];
        targetPosition[0] = rank;
        targetPosition[1] = file;

        // 데드존 세트
        if (OnlyCheckDeadZone(targetPosition))
            return;

        _OnlyCheckDeadZone(rank + rankDelta, file + fileDelta, rankDelta, fileDelta);
    }
}
