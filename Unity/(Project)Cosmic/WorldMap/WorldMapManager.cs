using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class WorldMapManager : MonoBehaviour
{

    static WorldMapManager _instance = null;

    public static WorldMapManager Instance()
    {
        return _instance;
    }

    
    public GameObject NotAnyMore_ui;
    public GameObject UseNav_ui;
    public GameObject Destination_ui;
    public GameObject Touch;
    public GameObject Notice;
    public GameObject ChooseStar;
    public bool dragState;

    public int zodiacCnt1;
    public int zodiacCnt2;
    public int zodiacCnt3;
    public int zodiacCnt4;
    public int zodiacCnt5;
    public int zodiacCnt6;
    public int zodiacCnt7;
    public int zodiacCnt8;
    public int zodiacCnt9;
    public int zodiacCnt10;
    public int zodiacCnt11;
    public int zodiacCnt12;

    bool cnt1 = false;
    bool cnt2 = false;
    bool cnt3 = false;
    bool cnt4 = false;
    bool cnt5 = false;
    bool cnt6 = false;
    bool cnt7 = false;
    bool cnt8 = false;
    bool cnt9 = false;
    bool cnt10 = false;
    bool cnt11 = false;
    bool cnt12 = false;

    void Start()
    {
        if (_instance == null)
            _instance = this;
        
        if(GameObject.Find("WorldMapFlag") == null)
        {
            GameObject.Find("ReturnButton").gameObject.GetComponent<Button>().onClick.AddListener(() => gameObject.GetComponent<ButtonController>().TransSceneToMain());
        }
        else
        {
            
            UseNav_ui.SetActive(false);
            Touch.SetActive(true);
            Touch.transform.FindChild("Choose").gameObject.SetActive(false);
            Notice.SetActive(true);
            Notice.GetComponentInChildren<Text>().CrossFadeAlpha(-1, 8.0f, false);
            //버튼 함수의 동적 할당
            //onClick.AddListener(() => gameObject.GetComponent<ButtonController>().TransSceneToManage(파라미터)); 파라미터 사용시
            //onClick.AddListener(gameObject.GetComponent<ButtonController>().TransSceneToManage); 파라미터 미사용시
            GameObject.Find("ReturnButton").gameObject.GetComponent<Button>().onClick.AddListener(() => gameObject.GetComponent<ButtonController>().TransSceneToManage());
        }
        loadStar();
    }
    void loadStar()
    {
        SelectDB.Instance().table = "zodiacTable";
        SelectDB.Instance().column = "Count(*)";
        SelectDB.Instance().Select(0);
        for (int i = 1; i <= SelectDB.Instance().starCount; i++)
        {
            SelectDB.Instance().table = "zodiacTable";
            SelectDB.Instance().column = "rowid, open, find, active, zID, zodiac";
            SelectDB.Instance().where = "WHERE \"rowid\" =" + i;
            SelectDB.Instance().Select(4);

            if (SelectDB.Instance().starActive == 0)
            {
                GameObject.Find(SelectDB.Instance().zodiacID).gameObject.GetComponent<SphereCollider>().enabled = true;
                GameObject.Find(SelectDB.Instance().zodiacID).gameObject.GetComponent<SphereCollider>().isTrigger = true;
            }
            else if (SelectDB.Instance().starActive == 1)
            {
                Debug.Log(SelectDB.Instance().zodiacName);
                if (SelectDB.Instance().zodiacName == "Aquarius")
                    WorldMapManager.Instance().zodiacCnt1 += 1;
                else if (SelectDB.Instance().zodiacName == "Pisces")
                    WorldMapManager.Instance().zodiacCnt2++;
                else if (SelectDB.Instance().zodiacName == "Aries")
                    WorldMapManager.Instance().zodiacCnt3++;
                else if (SelectDB.Instance().zodiacName == "Taurus")
                    WorldMapManager.Instance().zodiacCnt4++;
                else if (SelectDB.Instance().zodiacName == "Gemini")
                    WorldMapManager.Instance().zodiacCnt5++;
                else if (SelectDB.Instance().zodiacName == "Cancer")
                    WorldMapManager.Instance().zodiacCnt6++;
                else if (SelectDB.Instance().zodiacName == "Leo")
                    WorldMapManager.Instance().zodiacCnt7++;
                else if (SelectDB.Instance().zodiacName == "Virgo")
                    WorldMapManager.Instance().zodiacCnt8++;
                else if (SelectDB.Instance().zodiacName == "Libra")
                    WorldMapManager.Instance().zodiacCnt9++;
                else if (SelectDB.Instance().zodiacName == "Scorpius")
                    WorldMapManager.Instance().zodiacCnt10++;
                else if (SelectDB.Instance().zodiacName == "Sagittarius")
                    WorldMapManager.Instance().zodiacCnt11++;
                else if (SelectDB.Instance().zodiacName == "Capricornus")
                    WorldMapManager.Instance().zodiacCnt12++;
                GameObject.Find(SelectDB.Instance().zodiacID).gameObject.GetComponent<SphereCollider>().enabled = false;
                GameObject.Find(SelectDB.Instance().zodiacID).gameObject.GetComponent<MeshRenderer>().enabled = false;
            }
            if(zodiacCnt1 == 6 && cnt1 == false)
            {
                for(int cnt = 7; cnt < 17; cnt++)
                {
                    Debug.Log(GameObject.Find("Aquarius").transform.FindChild("aqua_" + cnt).name);
                    GameObject.Find("Aquarius").transform.FindChild("aqua_" + cnt).gameObject.GetComponent<SphereCollider>().enabled = false;
                    GameObject.Find("Aquarius").transform.FindChild("aqua_" + cnt).gameObject.GetComponent<MeshRenderer>().enabled = false;
                }
                cnt1 = true;
            }
            if(zodiacCnt2 == 5 && cnt2 == false)
            {
                for (int cnt = 6; cnt < 22; cnt++)
                {
                    GameObject.Find("Pisces").transform.FindChild("pis_" + cnt).gameObject.GetComponent<SphereCollider>().enabled = false;
                    GameObject.Find("Pisces").transform.FindChild("pis_" + cnt).gameObject.GetComponent<MeshRenderer>().enabled = false;
                }
                cnt2 = true;
            }
            //if (zodiacCnt3 == 4 && cnt3 == false)
            //{
            //    //작은별없음 Aries
            //  cnt3 == true;
            //}
            if (zodiacCnt4 == 6 && cnt4 == false)
            {
                for (int cnt = 7; cnt < 20; cnt++)
                {
                    GameObject.Find("Taurus").transform.FindChild("tau_" + cnt).gameObject.GetComponent<SphereCollider>().enabled = false;
                    GameObject.Find("Taurus").transform.FindChild("tau_" + cnt).gameObject.GetComponent<MeshRenderer>().enabled = false;
                }
                cnt4 = true;
            }
            if (zodiacCnt5 == 5 && cnt5 == false)
            {
                for (int cnt = 6; cnt < 18; cnt++)
                {
                    GameObject.Find("Gemini").transform.FindChild("gem_" + cnt).gameObject.GetComponent<SphereCollider>().enabled = false;
                    GameObject.Find("Gemini").transform.FindChild("gem_" + cnt).gameObject.GetComponent<MeshRenderer>().enabled = false;
                }
                cnt5 = true;
            }
            if (zodiacCnt6 == 5 && cnt6 == false)
            {
                for (int cnt = 6; cnt < 8; cnt++)
                {
                    GameObject.Find("Cancer").transform.FindChild("can_" + cnt).gameObject.GetComponent<SphereCollider>().enabled = false;
                    GameObject.Find("Cancer").transform.FindChild("can_" + cnt).gameObject.GetComponent<MeshRenderer>().enabled = false;
                }
                cnt6 = true;
            }
            if (zodiacCnt7 == 4 && cnt7 == false)
            {
                for (int cnt = 5; cnt < 17; cnt++)
                {
                    GameObject.Find("Leo").transform.FindChild("leo_" + cnt).gameObject.GetComponent<SphereCollider>().enabled = false;
                    GameObject.Find("Leo").transform.FindChild("leo_" + cnt).gameObject.GetComponent<MeshRenderer>().enabled = false;
                }
                cnt7 = true;
            }
            if (zodiacCnt8 == 5 && cnt8 == false)
            {
                for (int cnt = 6; cnt < 16; cnt++)
                {
                    GameObject.Find("Virgo").transform.FindChild("vir_" + cnt).gameObject.GetComponent<SphereCollider>().enabled = false;
                    GameObject.Find("Virgo").transform.FindChild("vir_" + cnt).gameObject.GetComponent<MeshRenderer>().enabled = false;
                }
                cnt8 = true;
            }
            if (zodiacCnt9 == 5 && cnt9 == false)
            {
                for (int cnt = 6; cnt < 7; cnt++)
                {
                    GameObject.Find("Libra").transform.FindChild("lib_" + cnt).gameObject.GetComponent<SphereCollider>().enabled = false;
                    GameObject.Find("Libra").transform.FindChild("lib_" + cnt).gameObject.GetComponent<MeshRenderer>().enabled = false;
                }
                cnt9 = true;
            }
            if (zodiacCnt10 == 6 && cnt10 == false)
            {
                for (int cnt = 7; cnt < 13; cnt++)
                {
                    GameObject.Find("Scorpius").transform.FindChild("sco_" + cnt).gameObject.GetComponent<SphereCollider>().enabled = false;
                    GameObject.Find("Scorpius").transform.FindChild("sco_" + cnt).gameObject.GetComponent<MeshRenderer>().enabled = false;
                }
                cnt10 = true;
            }
            if (zodiacCnt11 == 6 && cnt11 == false)
            {
                for (int cnt = 7; cnt < 22; cnt++)
                {
                    GameObject.Find("Sagittarius").transform.FindChild("sag_" + cnt).gameObject.GetComponent<SphereCollider>().enabled = false;
                    GameObject.Find("Sagittarius").transform.FindChild("sag_" + cnt).gameObject.GetComponent<MeshRenderer>().enabled = false;
                }
                cnt11 = true;
            }
            if (zodiacCnt12 == 6 && cnt12 == false)
            {
                for (int cnt = 7; cnt < 13; cnt++)
                {
                    GameObject.Find("Capricornus").transform.FindChild("cap_" + cnt).gameObject.GetComponent<SphereCollider>().enabled = false;
                    GameObject.Find("Capricornus").transform.FindChild("cap_" + cnt).gameObject.GetComponent<MeshRenderer>().enabled = false;
                }
                cnt12 = true;
            }

        }
    }


}
