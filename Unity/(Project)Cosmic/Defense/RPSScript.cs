using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;


public class RPSScript : MonoBehaviour {

    //가위 = 1, 바위 = 2, 보 = 3
    public List<int> myRPS = new List<int>();
    public List<int> comRPS = new List<int>();
    public int round;
    public int winCount;
    public int loseCount;
    public int drawCount;

    public int lastResult;  // 0: 무승부, 1: 성공, 2: 실패

    bool defenseEnd;

    [SerializeField]
    bool RoundState;
    [SerializeField]
    bool inputRPS;
    public int inputCnt;
    int RockCnt;
    int ScissorsCnt;
    int PaperCnt;

    void Start()
    {
        defenseEnd = false;
        lastResult = 0;
        RoundState = false;
        inputRPS = true;
        inputCnt = 0;
        RockCnt = 0;
        ScissorsCnt = 0;
        PaperCnt = 0;
        
        round = 0;
        winCount = 0;
        enemyRPS();
    }

    void Update()
    {
        if(inputRPS == true && inputCnt == 5)
        {
            inputRPS = false;
        }
        if(round == 5 && defenseEnd == false)
        {
            
            GameObject.Find("Main").transform.FindChild("Notice_Result").transform.FindChild("Success").GetComponent<Text>().text = winCount.ToString();
            GameObject.Find("Main").transform.FindChild("Notice_Result").transform.FindChild("Fail").GetComponent<Text>().text = loseCount.ToString();
            GameObject.Find("Main").transform.FindChild("Notice_Result").transform.FindChild("Draw").GetComponent<Text>().text = drawCount.ToString();

            GameObject.Find("Round").transform.FindChild("btn_round").gameObject.SetActive(false);
            StartCoroutine(delayResult());
            //UI 배치
            Hashtable hash = new Hashtable();
            hash.Add("x", 1);
            hash.Add("y", 1);
            hash.Add("z", 1);
            hash.Add("time", 0.5);
            iTween.ScaleTo(GameObject.Find("Main").transform.FindChild("Notice_Result").gameObject, hash);
            defenseEnd = true;
        }
    }

    public void enemyRPS()
    {
        for(int i=0; i < 5; i++)
        {
            comRPS.Add(checkOver2(Random.Range(1, 4)));
        }

    }

    public int checkOver2(int num)
    {
        if (comRPS.Count < 2)
        {
            return num;
        }

        int cnt = 0;

        for (int i = 0; i < comRPS.Count; i++)
        {
            if (comRPS[i] == num)
            {
                cnt++;
            }
        }


        if (cnt >= 2)
        {
            return checkOver2(Random.Range(1, 4));
        }
        else
        {
            return num;
        }

    }


    public void compare()
    {
        if (round >= 5)
        {
            return;
        }
        
        switch (myRPS[round])
        {
            case 1:
                ScissorsCnt--;
                GameObject.Find("Round_result").transform.FindChild("Player").transform.FindChild("Scissors").gameObject.SetActive(true);
                GameObject.Find("ScissorsCnt").gameObject.GetComponent<Text>().text = ScissorsCnt.ToString();
                break;
            case 2:
                RockCnt--;
                GameObject.Find("Round_result").transform.FindChild("Player").transform.FindChild("Rock").gameObject.SetActive(true);
                GameObject.Find("RockCnt").gameObject.GetComponent<Text>().text = RockCnt.ToString();
                break;
            case 3:
                PaperCnt--;
                GameObject.Find("Round_result").transform.FindChild("Player").transform.FindChild("Paper").gameObject.SetActive(true);
                GameObject.Find("PaperCnt").gameObject.GetComponent<Text>().text = PaperCnt.ToString();
                break;
            default:
                break;
        }

        switch (comRPS[round])
        {
            case 1:
                GameObject.Find("Round_result").transform.FindChild("Enemy").transform.FindChild("Scissors").gameObject.SetActive(true);
                break;
            case 2:
                GameObject.Find("Round_result").transform.FindChild("Enemy").transform.FindChild("Rock").gameObject.SetActive(true);
                break;
            case 3:
                GameObject.Find("Round_result").transform.FindChild("Enemy").transform.FindChild("Paper").gameObject.SetActive(true);
                break;
            default:
                break;
        }

        if (myRPS[round] == comRPS[round])
        {
            //비김
            drawCount++;
            lastResult = 0;
            GameObject.Find("Round").transform.FindChild("ResultText").gameObject.SetActive(true);
            GameObject.Find("Round").transform.FindChild("ResultText").gameObject.GetComponent<Text>().text = "무승부!";
            GameObject.Find("Round").transform.FindChild("ResultText").gameObject.GetComponent<Text>().color = Color.yellow;
            StartCoroutine(warningEnd());
        }
        else if ((myRPS[round] == 1 && comRPS[round] == 2) || (myRPS[round] == 2 && comRPS[round] == 3) || (myRPS[round] == 3 && comRPS[round] == 1))
        {
            //패배
            loseCount++;
            lastResult = 2;
            GameObject.Find("Round").transform.FindChild("ResultText").gameObject.SetActive(true);
            GameObject.Find("Round").transform.FindChild("ResultText").gameObject.GetComponent<Text>().text = "방어 실패!";
            GameObject.Find("Round").transform.FindChild("ResultText").gameObject.GetComponent<Text>().color = Color.red;
            StartCoroutine(warningEnd());
        }
        else
        {
            //승리
            winCount++;
            lastResult = 3;
            GameObject.Find("Round").transform.FindChild("ResultText").gameObject.SetActive(true);
            GameObject.Find("Round").transform.FindChild("ResultText").gameObject.GetComponent<Text>().text = "방어 성공!";
            GameObject.Find("Round").transform.FindChild("ResultText").gameObject.GetComponent<Text>().color = Color.green;
            StartCoroutine(warningEnd());
        }
        round++;
    }

    public void inputScissors()
    {
        if (ScissorsCnt == 2)
        {
            if (inputRPS == true)
            {
                GameObject.Find("Round").transform.FindChild("WaringText").gameObject.SetActive(true);
                StartCoroutine(warningEnd());
            }
        }

        if (myRPS.Count <= 4 && inputRPS == true && ScissorsCnt < 2)
        {
            myRPS.Add(1);
            inputCnt++;
            ScissorsCnt++;
        }
        

        if(inputRPS == false && RoundState == true)
        {
            compare();
            ScissorsCnt--;
        }
        GameObject.Find("ScissorsCnt").gameObject.GetComponent<Text>().text = ScissorsCnt.ToString();
    }

    public void inputRock()
    {
        if (RockCnt == 2)
        {
            if (inputRPS == true)
            {
                GameObject.Find("Round").transform.FindChild("WaringText").gameObject.SetActive(true);
                StartCoroutine(warningEnd());
            }
        }


        if (myRPS.Count <= 4 && inputRPS == true && RockCnt < 2)
        {
            myRPS.Add(2);
            inputCnt++;
            RockCnt++;
            
        }
        if (inputRPS == false && RoundState == true)
        {
            compare();
            RockCnt--;
        }
        GameObject.Find("RockCnt").gameObject.GetComponent<Text>().text = RockCnt.ToString();
    }

    public void inputPaper()
    {
        if (PaperCnt == 2)
        {
            if(inputRPS == true)
            {
                GameObject.Find("Round").transform.FindChild("WaringText").gameObject.SetActive(true);
                StartCoroutine(warningEnd());
            }
            
        }


        if (myRPS.Count <= 4 && inputRPS == true && PaperCnt < 2)
        {
            myRPS.Add(3);
            inputCnt++;
            PaperCnt++;
        }
        if (inputRPS == false && RoundState == true)
        {
            compare();
            PaperCnt--;
        }
        GameObject.Find("PaperCnt").gameObject.GetComponent<Text>().text = PaperCnt.ToString();
    }

    public void StartRound()
    {
        RoundState = true;
        if (inputRPS == false && RoundState == true)
        {
            compare();
            RoundState = false;
            if(round != 5)
            StartCoroutine(continueRound());
            else
            {
                GameObject.Find("Round").transform.FindChild("btn_round").gameObject.SetActive(false);
            }
        }
    }
    IEnumerator delayResult()
    {
        yield return new WaitForSeconds(3.0f);
        GameObject.Find("Round_result").transform.FindChild("Player").transform.FindChild("Scissors").gameObject.SetActive(false);
        GameObject.Find("Round_result").transform.FindChild("Player").transform.FindChild("Rock").gameObject.SetActive(false);
        GameObject.Find("Round_result").transform.FindChild("Player").transform.FindChild("Paper").gameObject.SetActive(false);

        GameObject.Find("Round_result").transform.FindChild("Enemy").transform.FindChild("Scissors").gameObject.SetActive(false);
        GameObject.Find("Round_result").transform.FindChild("Enemy").transform.FindChild("Rock").gameObject.SetActive(false);
        GameObject.Find("Round_result").transform.FindChild("Enemy").transform.FindChild("Paper").gameObject.SetActive(false);

        GameObject.Find("Main").transform.FindChild("Notice_Result").gameObject.SetActive(true);
    }
    IEnumerator warningEnd()
    {
        yield return new WaitForSeconds(2.4f);
        GameObject.Find("Round").transform.FindChild("WaringText").gameObject.SetActive(false);
        GameObject.Find("Round").transform.FindChild("ResultText").gameObject.SetActive(false);
    }

    IEnumerator continueRound()
    {
        GameObject.Find("btn_round").gameObject.SetActive(false);
        yield return new WaitForSeconds(3.5f);
        GameObject.Find("Round_result").transform.FindChild("Player").transform.FindChild("Scissors").gameObject.SetActive(false);
        GameObject.Find("Round_result").transform.FindChild("Player").transform.FindChild("Rock").gameObject.SetActive(false);
        GameObject.Find("Round_result").transform.FindChild("Player").transform.FindChild("Paper").gameObject.SetActive(false);

        GameObject.Find("Round_result").transform.FindChild("Enemy").transform.FindChild("Scissors").gameObject.SetActive(false);
        GameObject.Find("Round_result").transform.FindChild("Enemy").transform.FindChild("Rock").gameObject.SetActive(false);
        GameObject.Find("Round_result").transform.FindChild("Enemy").transform.FindChild("Paper").gameObject.SetActive(false);

        yield return new WaitForSeconds(0.5f);
        GameObject.Find("Round").transform.FindChild("btn_round").gameObject.SetActive(true);
    }
}
