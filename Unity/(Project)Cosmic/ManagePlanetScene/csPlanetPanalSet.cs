using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine.SceneManagement;


public class csPlanetPanalSet : MonoBehaviour {


    public static int PlanetCount;

    public GameObject PlanetExPanal;
    public Text txt;

    public GameObject deleteBtn;
    public GameObject warningPanal;

    public int PlanetNum;

    public GameObject SQLManager;

    void Start()
    {
        PlanetCount = MovePlanet.Instance.planets.Count;

        //setPanalVisible();
    }

    void Update()
    {
        

    }

    public void setPanalVisible()
    {
        PlanetExPanal.gameObject.SetActive(true);
    }
    
    public void setPanalNotVisible()
    {
        PlanetExPanal.gameObject.SetActive(false);
    }

    public void ChangeText(string pName)
    {
        txt.text = pName;
    }

    public void setVisibleBtn()
    {
        deleteBtn.SetActive(true);
    }

    public void notVisibleBtn()
    {
        deleteBtn.SetActive(false);
    }

    public void setWarning()
    {
        warningPanal.gameObject.SetActive(true);
        GameObject.Find("Manager").GetComponent<ManagePlanetRay>().enabled = false;

    }


    public void CancelInWarning()
    {
        warningPanal.gameObject.SetActive(false);
        GameObject.Find("Manager").GetComponent<ManagePlanetRay>().enabled = true;

    }

    public void DeleteInWarning()
    {
        string Query1;
        string Query2;
        SoundManager.Instance().PlaySfx(SoundManager.Instance().destroyPlanet);
        SoundManager.Instance().PlaySfx(SoundManager.Instance().SceneTran);
        Query1 = "Insert into garbageTable select name, size, color, locationX, locationY, locationZ, mat from managePlanetTable where rowid = " + PlanetNum;
        Debug.Log(Query1);

        Query2 = "delete from managePlanetTable where rowid = " + PlanetNum;
        Debug.Log(Query2);

        SQLManager.GetComponent<ManageSceneSQL>().UpdateQuery1(Query1);
        SQLManager.GetComponent<ManageSceneSQL>().DeleteQuery(Query2);

        SQLManager.GetComponent<ManageSceneSQL>().dbClose();

        //SoundManager.Instance().nextSceneName = "ManagePlanet";
        SceneManager.LoadScene("ManagePlanet");

    }
    
    public void btnDownHome()
    {
        string Query1;
        string Query2;

        Query1 = "UPDATE managePlanetTable SET User = 0";
        Debug.Log(Query1);
        Query2 = "UPDATE managePlanetTable SET User = 1 WHERE rowid = (select cPlanet FROM userTable)";
        Debug.Log(Query2);

        SQLManager.GetComponent<ManageSceneSQL>().UpdateQuery1(Query1);
        SQLManager.GetComponent<ManageSceneSQL>().UpdateQuery1(Query2);
        SQLManager.GetComponent<ManageSceneSQL>().dbClose();

        GameObject.Find("Manager/UIManager").GetComponent<ButtonController>().TransSceneToMain();

    }

}
