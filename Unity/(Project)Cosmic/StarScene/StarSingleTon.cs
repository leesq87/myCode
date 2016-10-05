using UnityEngine;
using UnityEngine.EventSystems;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;


public class StarSingleTon : MonoBehaviour {

    static StarSingleTon _instance = null;

    public static StarSingleTon Instance
    {
        get
        {
            return _instance;
        }
    }

    void Awake()
    {
        rowid = GameObject.Find("OBJ").GetComponent<OBJScript>().rowid;
        if (_instance == null)
            _instance = this;


    }


    public int cPlanet;
    public int cFood;
    public int cTitanium;
    public int cRE;
    public int cYE;
    public int cBE;
    public int cOE;
    public int cGE;
    public int cVE;
    public int cPE;
    public int shipNum;


    public int rowid;
    public string zID;
    public string zodiac;
    public string zName;
    public float locationX;
    public float locationY;
    public float locationZ;
    public bool zOpen;
    public bool zFind;
    public int needPE;
    public int nowPE;
    public bool zActive;


    public Text textFood;
    public Text textTitanium;
    public Text textPE;
    public Text textStarName;
    public Text textMainPE;

    public GameObject leftPE;
    public GameObject mainPointLight;
    public Sprite notInjection;


    void Start()
    {
        rowid = GameObject.Find("OBJ").GetComponent<OBJScript>().rowid;
        StarSceneSql.StarStart();


    }
    
    public void setMainText()
    {
        textFood.text = cFood.ToString();
        textTitanium.text = cTitanium.ToString();
        textPE.text = cPE.ToString();
        textStarName.text = zName;
        textMainPE.text = "현재:" + nowPE.ToString();

    }

    public void setPointlight()
    {
        if (needPE == nowPE)
        {
            leftPE.gameObject.SetActive(false);
            GameObject.Find("UI/Button/InjectionBtn").GetComponent<Button>().enabled = false;
            mainPointLight.gameObject.SetActive(true);
            GameObject.Find("UI/Button/InjectionBtn").GetComponent<Image>().sprite = notInjection;

            return;
        }
    }

}
