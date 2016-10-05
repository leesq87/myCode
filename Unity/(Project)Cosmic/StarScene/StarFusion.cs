using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System.Collections.Generic;


public class StarFusion : MonoBehaviour {


    public GameObject TextPENum;
    public GameObject TextOENum;
    public GameObject TextGENum;
    public GameObject TextVENum;
    public GameObject TextRENum;
    public GameObject TextYENum;
    public GameObject TextBENum;

    public GameObject SQLManager;

    public GameObject SubPanal1;
    public GameObject SubPanal2;

    public Slider slider1;
    public Text canNum1;
    public Text TextMin1;
    public Text TextMax1;
    public Text TextMakeNum1;
    public Text TextResultName1;
    public Text TextSum1Num;
    public Text textSum2Num;
    public Image ImgResult;
    public Image ImgSum1;
    public Image ImgSum2;

    public Slider slider2;
    public Text canNum2;
    public Text TextMin2;
    public Text TextMax2;
    public Text TextMakeNum2;
    public Text TextONum;
    public Text TextGNum;
    public Text TextVNum;


    public List<Sprite> EnergyIcon = new List<Sprite>();

    public GameObject resultPanal;
    public GameObject resultImg;
    public Text resultText;
    public Text quantityText;


    int switchEnergy = 0;
    public int maxE = 20000;


    public void setText()
    {
        TextPENum.GetComponent<Text>().text = StarSingleTon.Instance.cPE.ToString();
        TextOENum.GetComponent<Text>().text = StarSingleTon.Instance.cOE.ToString();
        TextGENum.GetComponent<Text>().text = StarSingleTon.Instance.cGE.ToString();
        TextVENum.GetComponent<Text>().text = StarSingleTon.Instance.cVE.ToString();
        TextRENum.GetComponent<Text>().text = StarSingleTon.Instance.cRE.ToString();
        TextYENum.GetComponent<Text>().text = StarSingleTon.Instance.cYE.ToString();
        TextBENum.GetComponent<Text>().text = StarSingleTon.Instance.cBE.ToString();
    }

    public void setIcon(int Result, int Sum1, int Sum2)
    {
        ImgResult.GetComponent<Image>().sprite = EnergyIcon[Result];
        ImgSum1.GetComponent<Image>().sprite = EnergyIcon[Sum1];
        ImgSum2.GetComponent<Image>().sprite = EnergyIcon[Sum2];

    }

    public void MakePE()
    {
        switchEnergy = 1;
        SubPanal2.SetActive(true);
        canMakeNum(StarSingleTon.Instance.cPE, StarSingleTon.Instance.cOE,StarSingleTon.Instance.cGE, StarSingleTon.Instance.cVE);

        TextONum.text = StarSingleTon.Instance.cOE.ToString();
        TextGNum.text = StarSingleTon.Instance.cGE.ToString();
        TextVNum.text = StarSingleTon.Instance.cVE.ToString();

    }


    public void MakeOE()
    {
        switchEnergy = 2;
        SubPanal1.SetActive(true);
        setIcon(1, 4, 5);
        canMakeNum(StarSingleTon.Instance.cOE, StarSingleTon.Instance.cRE, StarSingleTon.Instance.cYE);
        TextResultName1.text = "오렌지";
        TextSum1Num.text = StarSingleTon.Instance.cRE.ToString();
        textSum2Num.text = StarSingleTon.Instance.cYE.ToString();

    }

    public void MakeGE()
    {
        switchEnergy = 3;
        SubPanal1.SetActive(true);
        setIcon(2, 5, 6);
        canMakeNum(StarSingleTon.Instance.cGE, StarSingleTon.Instance.cYE, StarSingleTon.Instance.cBE);
        TextResultName1.text = "그린";
        TextSum1Num.text = StarSingleTon.Instance.cYE.ToString();
        textSum2Num.text = StarSingleTon.Instance.cBE.ToString();


    }

    public void MakeVE()
    {
        switchEnergy = 4;
        SubPanal1.SetActive(true);
        setIcon(3, 4, 6);
        canMakeNum(StarSingleTon.Instance.cVE, StarSingleTon.Instance.cRE, StarSingleTon.Instance.cBE);
        TextResultName1.text = "바이올렛";
        TextSum1Num.text = StarSingleTon.Instance.cRE.ToString();
        textSum2Num.text = StarSingleTon.Instance.cBE.ToString();

    }


    void canMakeNum(int resutl, int sum1, int sum2, int sum3)
    {
        int min = 0;
        if (sum1 <= sum2 && sum1 <= sum3)
            min = sum1;
        if (sum2 <= sum1 && sum2 <= sum3)
            min = sum2;
        if (sum3 <= sum1 && sum3 <= sum2)
            min = sum3;

        switch (switchEnergy)
        {
            case 1:
                if (StarSingleTon.Instance.cPE + min > maxE)
                {
                    min = (StarSingleTon.Instance.cPE + min) - maxE;

                }
                break;

            case 2:
                if (StarSingleTon.Instance.cOE + min > maxE)
                {
                    min = (StarSingleTon.Instance.cOE + min) - maxE;
                }
                break;

            case 3:
                if (StarSingleTon.Instance.cGE + min > maxE)
                {
                    min = (StarSingleTon.Instance.cGE + min) - maxE;
                }
                break;

            case 4:
                if (StarSingleTon.Instance.cVE + min > maxE)
                {
                    min = (StarSingleTon.Instance.cVE + min) - maxE;
                }
                break;
            default:
                break;
        }
        TextMax2.text = min + "";
        slider2.maxValue = min;
        canNum2.text = min.ToString();
    }



    void canMakeNum(int resutl, int sum1, int sum3)
    {
        int min = 0;
        if (sum1 <= sum3)
            min = sum1;
        else
            min = sum3;
        TextMax1.text = min + "";
        slider1.maxValue = min;
        canNum1.text = min.ToString();
    }


    public void ChangeSliderValue1()
    {
        float val = slider1.value;
        UpdateText1((int)val);
    }

    public void UpdateText1(int cnt)
    {
        TextMakeNum1.text = cnt + "";
    }



    public void ChangeSliderValue2()
    {
        float val = slider2.value;
        UpdateText2((int)val);
    }

    public void UpdateText2(int cnt)
    {
        TextMakeNum2.text = cnt + "";
    }



    public void ConfirmInSubPanal()
    {
        int makeNum;

        string Query = "";

        switch (switchEnergy)
        {
            case 1: //pletinum = orange + green + violate 1:1:1

                makeNum = System.Convert.ToInt32(TextMakeNum2.text);
                StarSingleTon.Instance.cPE += makeNum;
                StarSingleTon.Instance.cOE -= makeNum;
                StarSingleTon.Instance.cGE -= makeNum;
                StarSingleTon.Instance.cVE -= makeNum;
                Query = "UPDATE userTable SET cPE = " + StarSingleTon.Instance.cPE
                    + ", cOE = " + StarSingleTon.Instance.cOE + ", cGE = " + StarSingleTon.Instance.cGE
                    + ", cVE = " + StarSingleTon.Instance.cVE + " WHERE cPE = " + (StarSingleTon.Instance.cPE - makeNum);
                ResultOpen(0, makeNum);
                break;

            case 2: // orange = red + yellow 1:1

                makeNum = System.Convert.ToInt32(TextMakeNum1.text);

                StarSingleTon.Instance.cOE += makeNum;
                StarSingleTon.Instance.cRE -= makeNum;
                StarSingleTon.Instance.cYE -= makeNum;
                Query = "UPDATE userTable SET cOE = " + StarSingleTon.Instance.cOE
                    + ", cRE = " + StarSingleTon.Instance.cRE + ", cYE = " + StarSingleTon.Instance.cYE
                    + " WHERE cOE = " + (StarSingleTon.Instance.cOE - makeNum);
                ResultOpen(1, makeNum);

                break;

            case 3: //green = ytellow + blue 1:1
                makeNum = System.Convert.ToInt32(TextMakeNum1.text);

                StarSingleTon.Instance.cGE += makeNum;
                StarSingleTon.Instance.cYE -= makeNum;
                StarSingleTon.Instance.cBE -= makeNum;
                Query = "UPDATE userTable SET cGE = " + StarSingleTon.Instance.cGE
                      + ", cYE = " + StarSingleTon.Instance.cYE + ", cBE = " + StarSingleTon.Instance.cBE
                        + " WHERE cGE = " + (StarSingleTon.Instance.cGE - makeNum);
                ResultOpen(2, makeNum);

                break;

            case 4: // violate = red + blue 1:1
                makeNum = System.Convert.ToInt32(TextMakeNum1.text);

                StarSingleTon.Instance.cVE += makeNum;
                StarSingleTon.Instance.cRE -= makeNum;
                StarSingleTon.Instance.cBE -= makeNum;
                Query = "UPDATE userTable SET cVE = " + StarSingleTon.Instance.cVE
                    + ", cRE = " + StarSingleTon.Instance.cRE + ", cBE = " + StarSingleTon.Instance.cBE
                    + " WHERE cVE = " + (StarSingleTon.Instance.cVE - makeNum);
                ResultOpen(3, makeNum);
                break;

            default:
                break;

        }


        TextMakeNum1.text = 0 + "";
        slider1.value = 0;

        TextMakeNum2.text = 0 + "";
        slider2.value = 0;

        switchEnergy = 0;
        SQLManager.GetComponent<StarSceneSql>().UpdateQuery(Query);
        SubPanal1.SetActive(false);
        SubPanal2.SetActive(false);

        setText();

    }


    public void CancelInSubPanal()
    {
        TextMakeNum1.text = 0 + "";
        slider1.value = 0;
        TextMakeNum2.text = 0 + "";
        slider2.value = 0;
        switchEnergy = 0;
        SubPanal1.SetActive(false);
        SubPanal2.SetActive(false);

        setText();

    }

    public void ResultOpen(int num, int makeNum)
    {
        resultPanal.gameObject.SetActive(true);
        quantityText.text = makeNum.ToString();

        switch (num)
        {
            case 0:
                resultImg.GetComponent<Image>().sprite = EnergyIcon[num];
                resultText.text = "플래티넘";
                break;

            case 1:
                resultImg.GetComponent<Image>().sprite = EnergyIcon[num];
                resultText.text = "오렌지";
                break;

            case 2:
                resultImg.GetComponent<Image>().sprite = EnergyIcon[num];
                resultText.text = "그린";
                break;

            case 3:
                resultImg.GetComponent<Image>().sprite = EnergyIcon[num];
                resultText.text = "바이올렛";
                break;

            default:
                break;

        }

    }

    public void ConfrimInResult()
    {
        resultPanal.gameObject.SetActive(false);
    }
}
