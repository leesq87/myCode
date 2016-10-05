using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class ExploreState : MonoBehaviour {
    int maxFood;
    bool warning = false;
    public GameObject warning_ui;
    public GameObject notanymore_ui;

    void Update()
    {
        if (MainSingleTon.Instance.shipTouch == true)
        {
            SelectDB.Instance().column = "cFood, shipNum";
            SelectDB.Instance().table = "userTable";
            //SelectDB.Instance().where = "WHERE zID= " + "'" + hit.transform.name + "'";
            SelectDB.Instance().Select(2);

            SelectDB.Instance().table = "managePlanetTable";
            SelectDB.Instance().column = "Count(*)";
            SelectDB.Instance().Select(0);

            SelectDB.Instance().table = "zodiacTable";
            SelectDB.Instance().column = "Count(*)";
            SelectDB.Instance().where = "WHERE \"open\" = 1 AND  \"find\" = 1 AND \"active\" = 0";
            SelectDB.Instance().Select(0);

            GameData.Instance().shipNum = SelectDB.Instance().shipNum;
            switch (SelectDB.Instance().shipNum)
            {
                case 1:
                    maxFood = 300;
                    break;
                case 2:
                    maxFood = 350;
                    break;
                case 3:
                    maxFood = 400;
                    break;
                case 4:
                    maxFood = 600;
                    break;
                case 5:
                    maxFood = 700;
                    break;
            }
            
            if (SelectDB.Instance().food < maxFood)
            {
                MainSingleTon.Instance.shipTouch = false;
                GameObject.Find("UI").gameObject.GetComponent<csScreenPointTouch>().enabled = false;
                warning_ui.SetActive(true);
                warning_ui.transform.FindChild("Food").GetComponent<Text>().text = maxFood.ToString();
                StartCoroutine(returnMain());
            }
            else if(SelectDB.Instance().food >= maxFood)
            {
                MainSingleTon.Instance.shipTouch = false;
                if (SelectDB.Instance().planetCount + SelectDB.Instance().starCount == 16)
                {
                    GameObject.Find("UI").gameObject.GetComponent<csScreenPointTouch>().enabled = false;
                    notanymore_ui.SetActive(true);
                }
                else
                {
                    GameData.Instance().maxFuel = maxFood;
                    transScenetoMap();
                }
                
            }
            
        }
    }
	
    IEnumerator returnMain()
    {
        //현재 사용하지 않음
        //yield return new WaitForSeconds(1.0f);
        //GameObject.Find("returnSec").gameObject.GetComponentInChildren<Text>().text = "2";
        //yield return new WaitForSeconds(1.0f);
        //GameObject.Find("returnSec").gameObject.GetComponentInChildren<Text>().text = "1";
        //yield return new WaitForSeconds(1.0f);
        //GameObject.Find("returnSec").gameObject.GetComponentInChildren<Text>().text = "0";
        //GameObject.Find("WorldMapManager").gameObject.GetComponent<ButtonController>().TransSceneToMain();
        yield return new WaitForSeconds(3.0f);
        
        warning_ui.SetActive(false);
        GameObject.Find("UI").gameObject.GetComponent<csScreenPointTouch>().enabled = true;
    }

    void transScenetoMap()
    {
        GameObject.Find("UIManager").gameObject.GetComponent<ButtonController>().TransSceneToMap();
    }

    public void notanymoreFalse()
    {
        notanymore_ui.SetActive(false);
        GameObject.Find("UI").gameObject.GetComponent<csScreenPointTouch>().enabled = true;
    }
}
