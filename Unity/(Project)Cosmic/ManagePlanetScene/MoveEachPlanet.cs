using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class MoveEachPlanet : MonoBehaviour
{
    int POS_MAX = 0;
    Queue<int> nextPos = new Queue<int>();
    public int lastPos = 0;    
    public float stepAmount = 10;
    public bool onMoving = false;
    public int curPos = 0;
    int listCount;
    public bool center;

    csPlanetPanalSet script;

    void Start()
    {
        POS_MAX = MovePlanet.Instance.points.Count - 1;
        StartCoroutine(CheckMove());
        script = GameObject.Find("Manager/UIManager").GetComponent<csPlanetPanalSet>();
        // SQL에서 행성 갯수 체크후 생성된 Way Point의 중간값 지정
        if (MovePlanet.Instance.points.Count <= 7)
        {
            listCount = MovePlanet.Instance.points.Count / 2;
        }
        else if (MovePlanet.Instance.points.Count < 10)
        {
            if (MovePlanet.Instance.points.Count % 2 == 0)
            {
                listCount = (MovePlanet.Instance.points.Count) / 2;
            }
            else
            {
                listCount = (MovePlanet.Instance.points.Count / 2) + 1;
            }
        }
        else
        {
            listCount = 6;
        }
        center = false;
    }

    void Update()
    {
        if (onMoving)
        {
            script.setPanalNotVisible();
            return;
        }

        script.setPanalVisible();
        center = false;
        if (curPos == listCount)
        {
            center = true;
            if (this.gameObject.GetComponent<PlanetInfo>())
            {
                if (this.gameObject.GetComponent<PlanetInfo>().rowid == MovePlanet.Instance.cPlanet)
                {
                    script.notVisibleBtn();
                }
                else
                {
                    script.setVisibleBtn();

                }
                script.ChangeText(this.gameObject.GetComponent<PlanetInfo>().pName);
                script.PlanetNum = this.gameObject.GetComponent<PlanetInfo>().rowid;


            }
            if (this.gameObject.GetComponent<StarInfo>())
            {
                script.ChangeText(this.gameObject.GetComponent<StarInfo>().zName);
                script.notVisibleBtn();
            }
        }
    }

    public void Stop()
    {
        nextPos.Clear();
    }

    public void MoveNext()
    {
        lastPos += 1;
        if (lastPos > POS_MAX) lastPos = 0;
        nextPos.Enqueue(lastPos);

    }

    public void MovePrev()
    {
        lastPos -= 1;
        if (lastPos < 0) lastPos = POS_MAX;
        nextPos.Enqueue(lastPos);
    }

    IEnumerator CheckMove()
    {
        while (true)
        {
            yield return null;
            if (nextPos.Count > 0 && csPlanetPanalSet.PlanetCount<=5)
            {
                onMoving = true;
                yield return StartCoroutine(MoveCoroutineLess5());
                onMoving = false;
            }

            if (nextPos.Count>0 && csPlanetPanalSet.PlanetCount > 5)
            {
                onMoving = true;
                yield return StartCoroutine(MoveCoroutineMore5());
                onMoving = false;
            }
        }
    }

    //loop, 5개이하
    IEnumerator MoveCoroutineLess5()
    {
        float step = 0;
        int targetPos = nextPos.Peek();
        Transform target = MovePlanet.Instance.points[targetPos];
        target = MovePlanet.Instance.points[targetPos];
        float curTime = 0;
        Vector3 start = new Vector3(this.transform.position.x, this.transform.position.y, this.transform.position.z);
        Vector3 end = target.transform.position;

        while (curTime / MovePlanet.Instance.moveTime <= 1)
        {
            yield return null;
            if (curTime > MovePlanet.Instance.moveTime)
                curTime = MovePlanet.Instance.moveTime;
            Vector3 now = Vector3.Lerp(start, end, curTime / MovePlanet.Instance.moveTime);
            transform.position = now;
            curTime += Time.deltaTime * MovePlanet.Instance.addTime;
        }
        curPos = lastPos;

        if (nextPos.Count > 0)
            nextPos.Dequeue();
    }
    //이동 5개초과
    IEnumerator MoveCoroutineMore5()
    {
        float step = 0;
        int targetPos = nextPos.Peek();
        Transform target = MovePlanet.Instance.points[targetPos];
        if (targetPos == 0 && curPos == POS_MAX)
        {
            this.transform.position = target.position * 1000;
            yield return new WaitForSeconds(0.4f);
            this.transform.position = target.position;
        }
        else if (targetPos == POS_MAX && curPos == 0)
        {
            this.transform.position = target.position * 1000;
            yield return new WaitForSeconds(0.4f);
            this.transform.position = target.position;
        }
        else
        {
            target = MovePlanet.Instance.points[targetPos];
            while (Vector3.Distance(this.transform.position, target.transform.position) > 0.05f)
            {
                yield return null;
                step = stepAmount * Time.deltaTime;
                transform.position = Vector3.MoveTowards(this.transform.position, target.transform.position, step);
            }
        }
        curPos = lastPos;
        if (nextPos.Count > 0)
            nextPos.Dequeue();
    }
}

/* 키보드 조작
public class MoveEachPlanet : MonoBehaviour
{
    int POS_MAX = 0;

    Queue<int> nextPos = new Queue<int>();
    public int lastPos = 0;
    public float stepAmount = 10;

    public bool onMoving = false;

    public int curPos = 0;


    void Start()
    {
        POS_MAX = MovePlanet.Instance.points.Count - 1;
        StartCoroutine(CheckMove());
    }

    public void Stop()
    {
        nextPos.Clear();
    }

    public void MoveNext()
    {
        //Debug.Log("Next");
        lastPos += 1;
        if (lastPos > POS_MAX) lastPos = 0;

        nextPos.Enqueue(lastPos);

    }

    public void MovePrev()
    {
        //Debug.Log("Prev");
        lastPos -= 1;
        if (lastPos < 0) lastPos = POS_MAX;

        nextPos.Enqueue(lastPos);
    }

    IEnumerator CheckMove()
    {
        while (true)
        {
            yield return null;


            if (nextPos.Count > 0)
            {
                onMoving = true;
                yield return StartCoroutine(MoveCoroutine());
                onMoving = false;
            }
        }
    }

    //IEnumerator MoveCoroutine()
    //{
    //    float step = 0;
    //    int targetPos = nextPos.Peek();

    //    Transform target = MovePlanet.Instance.points[targetPos];

    //    target = MovePlanet.Instance.points[targetPos];

    //    float curTime = 0;

    //    Vector3 start = new Vector3(this.transform.position.x, this.transform.position.y, this.transform.position.z);
    //    Vector3 end = target.transform.position;

    //    while (curTime / MovePlanet.Instance.moveTime <= 1)
    //    {
    //        yield return null;

    //        if (curTime > MovePlanet.Instance.moveTime) curTime = MovePlanet.Instance.moveTime;

    //        Vector3 now = Vector3.Lerp(start, end, curTime / MovePlanet.Instance.moveTime);
    //        transform.position = now;

    //        curTime += Time.deltaTime * MovePlanet.Instance.addTime;
    //    }

    //    curPos = lastPos;

    //    if (nextPos.Count > 0)
    //        nextPos.Dequeue();
    //}


    //순간이동
    //5개미만
    IEnumerator MoveCoroutine()
    {
        float step = 0;

        int targetPos = nextPos.Peek();

        Transform target = MovePlanet.Instance.points[targetPos];

        if (targetPos == 0 && curPos == POS_MAX)
        {
            this.transform.position = target.position * 1000;
            yield return new WaitForSeconds(0.4f);
            this.transform.position = target.position;
        }
        else if (targetPos == POS_MAX && curPos == 0)
        {
            this.transform.position = target.position * 1000;
            yield return new WaitForSeconds(0.4f);
            this.transform.position = target.position;
        }
        else
        {

            target = MovePlanet.Instance.points[targetPos];

            while (Vector3.Distance(this.transform.position, target.transform.position) > 0.05f)
            {
                yield return null;

                step = stepAmount * Time.deltaTime;
                transform.position = Vector3.MoveTowards(this.transform.position, target.transform.position, step);
            }

        }

        curPos = lastPos;

        if (nextPos.Count > 0)
            nextPos.Dequeue();
    }
}
*/