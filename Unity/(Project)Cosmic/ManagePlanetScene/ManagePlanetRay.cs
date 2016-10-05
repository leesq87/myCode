using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class ManagePlanetRay : MonoBehaviour {

    public static bool dragging;

    public GameObject SQLManager;

    void Start()
    {
        dragging = false;
    }

    void Update()
    {

        //if (Input.touchCount != 0)
        if (Input.GetButtonUp("Fire1"))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;

            if (Physics.Raycast(ray, out hit))
            {
                
                if(hit.transform.tag == "Stars")
                {
                    Debug.Log("sttt");
                    SoundManager.Instance().PlaySfx(SoundManager.Instance().planetTouch);
                    if (hit.transform.GetComponent<MoveEachPlanet>().center && hit.transform.GetComponent<StarInfo>())
                    {
                            Debug.Log("center");
                        GameObject.Find("OBJ").GetComponent<OBJScript>().rowid = hit.transform.GetComponent<StarInfo>().rowid;
                        DontDestroyOnLoad(GameObject.Find("OBJ").gameObject);

                        SQLManager.GetComponent<ManageSceneSQL>().dbClose();
                        SoundManager.Instance().nextSceneName = "Star";
                        SceneManager.LoadScene("loading");
                    }
                }

                if (!(hit.transform.name == "Myplanet"))
                {
                    SoundManager.Instance().PlaySfx(SoundManager.Instance().planetTouch);
                    if (hit.transform.GetComponent<MoveEachPlanet>().center && !(hit.transform.tag == "Stars"))
                    {

                        string Query1 = "UPDATE managePlanetTable SET User = 0";
                        Debug.Log(Query1);

                        string Query2 = "UPDATE managePlanetTable SET User = 1 Where rowid = " + hit.transform.GetComponent<PlanetInfo>().rowid;
                        Debug.Log(Query2);

                        SQLManager.GetComponent<ManageSceneSQL>().UpdateQuery1(Query1);
                        SQLManager.GetComponent<ManageSceneSQL>().UpdateQuery1(Query2);
                        SQLManager.GetComponent<ManageSceneSQL>().dbClose();

                        SoundManager.Instance().nextSceneName = "Planet";
                        SceneManager.LoadScene("loading");

                    }
                }

            }
        }

    }

}
