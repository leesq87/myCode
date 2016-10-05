using UnityEngine;
using System.Collections;
using UnityEngine.UI;


public class csInjection : MonoBehaviour {



    int minimum;
    int maximun;
    int nowE;

    int userE;
    int PlanetE;

    public Text havePE;
    public Text needPE;

    public Slider slider;
    public Text textMaxPE;
    public Text textMakeNum;

    public GameObject SQLManager;

    public GameObject ResultPanal;
    public Text quantityText;


    public void setPanal()
    {
        havePE.text = StarSingleTon.Instance.cPE.ToString();
        needPE.text = (StarSingleTon.Instance.needPE - StarSingleTon.Instance.nowPE).ToString();

        userE = StarSingleTon.Instance.cPE;
        PlanetE = (StarSingleTon.Instance.needPE - StarSingleTon.Instance.nowPE);


        minimum = 0;
        nowE = 0;
        setMaximunPE();
    }


    void setMaximunPE()
    {
        //잔존량 > 유저보유량 -> max = 유저량
        //잔존량<= 유저보유량 -> max = 보유량

        if(PlanetE > userE)
        {
            slider.GetComponent<Slider>().maxValue = userE;
        }
        else
        {
            slider.GetComponent<Slider>().maxValue = PlanetE;
        }

        textMaxPE.text = slider.GetComponent<Slider>().maxValue.ToString();

    }

    public void ChangeSliderValue()
    {
        float val = slider.value;

        UpdateText((int)val);
        

    }

    public void UpdateText(int cnt)
    {
        textMakeNum.text = cnt.ToString();
    }



    public void Confirm()
    {
        string Query;
        string Query2;
        SoundManager.Instance().PlaySfx(SoundManager.Instance().usePe);
        StarSingleTon.Instance.nowPE += System.Convert.ToInt32(textMakeNum.text);
        StarSingleTon.Instance.cPE -= System.Convert.ToInt32(textMakeNum.text);

        Query2 = "UPDATE userTable SET cPE = " + StarSingleTon.Instance.cPE;
        Debug.Log(Query2);

        if(StarSingleTon.Instance.needPE == StarSingleTon.Instance.nowPE)
        {
            SoundManager.Instance().PlaySfx(SoundManager.Instance().activeStar);
            Query = "UPDATE zodiacTable SET nowPE = " + StarSingleTon.Instance.nowPE + ", active = " + 1 +  " WHERE rowid = " + StarSingleTon.Instance.rowid;
            Debug.Log(Query);
        }
        else
        {
            Query = "UPDATE zodiacTable SET nowPE = " + StarSingleTon.Instance.nowPE + " WHERE rowid = " + StarSingleTon.Instance.rowid;
            Debug.Log(Query);
        }
        SQLManager.GetComponent<StarSceneSql>().UpdateQuery(Query);
        SQLManager.GetComponent<StarSceneSql>().UpdateQuery(Query2);


        openResult();
        GameObject.Find("UI/Injection_PE").gameObject.SetActive(false);
    }

    public void Cancel()
    {
        slider.value = 0;
        GameObject.Find("UI/Injection_PE").gameObject.SetActive(false);
    }

    public void openResult()
    {
        ResultPanal.gameObject.SetActive(true);
        quantityText.text = StarSingleTon.Instance.cPE.ToString();
    }

    public void confirnInResult()
    {
        ResultPanal.gameObject.SetActive(false);
        StarSingleTon.Instance.setPointlight();
    }


}

