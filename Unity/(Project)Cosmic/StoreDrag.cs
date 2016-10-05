using UnityEngine;
using System.Collections;
using UnityEngine.EventSystems;
using UnityEngine.UI;


public class StoreDrag : ScrollRect {

    //1페이지의 폭
    private float pageWidth;
    
    //이전페이지의 index 가장 왼쪽을 0으로
    private int prevPageIndex = 0;

    bool sDrag = false;
    Vector2 finVec2 = new Vector2(0f,0f);
    Vector2 nowVec2 = new Vector2(0f, 0f);


    int nowY;
    int finY;

    protected override void Awake()
    {
        base.Awake();
        
        
        GridLayoutGroup grid = content.GetComponent<GridLayoutGroup>();

        //1페이지의 폭을 받아온다
        //x축
        pageWidth = grid.cellSize.y + grid.spacing.y;

        Debug.Log(grid);
        Debug.Log(pageWidth);


    }

    public override void OnBeginDrag(PointerEventData eventData)
    {
        base.OnBeginDrag(eventData);
        sDrag = true;
        
    }

    public override void OnEndDrag(PointerEventData eventData)
    {
        base.OnEndDrag(eventData);

        //드래그를 종료했을때, 스크롤멈춤
        //스냅 할 페이지가 가져오던 후에도 관성이 효과가 버리므로
        StopMovement();
        
        //스냅할 페이지 결정
        //스냅할 페이지의 인덱스 결정
        int pageIndex = Mathf.RoundToInt(content.anchoredPosition.y / pageWidth);

        //페이지가 변경되지 않거나 빠르게 드래그한 경우
        //드래그의 양의 상태를 조정
        if (pageIndex == prevPageIndex && Mathf.Abs(eventData.delta.y) >= 5)
        {
            pageIndex += (int)Mathf.Sign(eventData.delta.y);
        }

        //content 스크롤 위치를 결정
        //반드시 페이지에 스냅할 수 있는 위치가 될것이 포인트
        int destX = pageIndex * System.Convert.ToInt32(pageWidth);
        //content.anchoredPosition = new Vector2(0f, content.anchoredPosition.y);
        finVec2 = new Vector2(0f, destX);
        nowVec2 = content.anchoredPosition;

        //content.anchoredPosition = new Vector2(0f, destX);

        Debug.Log(finVec2);
        Debug.Log(nowVec2);

        //content.anchoredPosition=Vector2.MoveTowards(content.anchoredPosition, finVec2, 0.5f);
        // 페이지가 변경되지 않은 판정을 위한 마지막 스냅되어 있는 페이지를 기억
        prevPageIndex = pageIndex;
        sDrag = false;
        finY = System.Convert.ToInt32(finVec2.y);
        nowY = System.Convert.ToInt32(nowVec2.y);
        finVec2.y = finY;
        nowVec2.y = nowY;

    }

    int a = 0;

    void Update()
    {
        if (!sDrag)
        {
            if(finY != nowY)
            {
                if(nowY <finY)
                {
                    nowY = nowY +15;
                    if (Mathf.Abs(nowY-finY) < 15)
                    {
                        nowY = finY;
                    }
                    content.anchoredPosition = new Vector2(0f, nowY);

                }
                else
                {
                    nowY = nowY -15;
                    if (Mathf.Abs(nowY - finY) < 15)
                    {
                        nowY = finY;
                    }
                    content.anchoredPosition = new Vector2(0f, nowY);
                }
            }
        }

    }

}
