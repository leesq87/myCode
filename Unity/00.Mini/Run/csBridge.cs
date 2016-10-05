using UnityEngine;
using System.Collections;

public class csBridge : MonoBehaviour {

    public GameObject[] bridges;
    public GameObject[] coins;
    public GameObject bridgeTurn;

    GameObject newBridge;
    GameObject childBirdge;
    GameObject oldBridge;

    GameObject bridge;
    GameObject coin;
    bool canCoin = false;

    int dir = 0;
    Quaternion quatAng;

    void Start()
    {
        newBridge = GameObject.Find("StartBridge");
        oldBridge = GameObject.Find("OldBridge");
        childBirdge = newBridge;

        makeBridge("FORWARD");

    }
    
    //다리만들기
    void makeBridge(string sDir)
    {
        DeleteOldBridge();
        CalcRotation(sDir);
        MakeNewBridge();
    }

    //지나간 다리 삭제
    void DeleteOldBridge()
    {
        Destroy(oldBridge);
        oldBridge = newBridge;

        //다리 시작점 만들기
        newBridge = new GameObject("StartBridge");
    }

    //회전방향과 각도계산
    void CalcRotation(string sDir)
    {
        switch (sDir)
        {
            case "LEFT":
                dir--;
                break;
            case "RIGHT":
                dir++;
                break;
        }

        if (dir < 0)
            dir = 3;
        if (dir > 3)
            dir = 0;

        quatAng.eulerAngles = new Vector3(0, dir * 90, 0);
    }

    //새로운 다리 만들기
    void MakeNewBridge()
    {
        for (int i = 0; i < 10; i++)
        {
            bridge = bridges[0];
            coin = coins[Random.Range(0, 3)];
            canCoin = false;

            SelectBridge(i);
            Vector3 pos = Vector3.zero;

            Vector3 localpos = childBirdge.transform.localPosition;

            switch (dir)
            {
                case 0:
                    pos = new Vector3(localpos.x, 0, localpos.z + 10);
                    break;
                case 1:
                    pos = new Vector3(localpos.x + 10, 0, localpos.z);
                    break;
                case 2:
                    pos = new Vector3(localpos.x, 0, localpos.z - 10);
                    break;
                case 3:
                    pos = new Vector3(localpos.x - 10, 0, localpos.z);
                    break;
            }

            childBirdge = Instantiate(bridge, pos, quatAng) as GameObject;
            childBirdge.transform.parent = newBridge.transform;

            if (canCoin)
            {
                childBirdge = Instantiate(coin, pos, quatAng) as GameObject;
                childBirdge.transform.parent = newBridge.transform;
            }
        }
    }

    //다리종류 설정
    void SelectBridge(int n)
    {
        switch (n)
        {
            case 9:
                bridge = bridgeTurn;
                break;
            case 1:
            case 3:
            case 5:
            case 7:
                bridge = bridges[Random.Range(0, bridges.Length)];
                break;
            default:
                if (Random.Range(0, 100) > 50)
                {
                    canCoin = true;
                }
                break;
        }
    }


}
