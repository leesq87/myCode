using UnityEngine;
using UnityEngine.EventSystems;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;

public class MainSingleTon : MonoBehaviour {

    static MainSingleTon _instance = null;

    public static MainSingleTon Instance
    {
        get
        {
            return _instance;
        }
    }
    //color) 1= blue, 2= red , 3= yellow, 4= violate, 5= green, 6 = Orange
    //size) 1= small, 2 = midium, 3= large, 4= xlarge
    //mat ) 1= 1, 2=2, 3=3
    //list입력관련 (Color)(Size)(Mat) -> 변경순서mat->size->color

    void Awake()
    {
        if (_instance == null)
            _instance = this;
        int count = 0;
        for (int i = 1; i <= 6; i++)
        {
            for (int j = 1; j <= 4; j++)
            {
                for (int k = 1; k <= 3; k++)
                {
                    D_PlanetList.Add(i * 100 + j * 10 + k, PlanetList[count]);
                    count++;
                }
            }
        }
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
    public string pName;
    public int size;
    public int color;
    public int mat;
    public int mFood;
    public int mTitanium;
    public float locationX;
    public float locationY;
    public float locationZ;
    public int le_persec;
    public bool position_house;
    public int state;
    public bool user;
    public int neighbor;
    public int lFood;
    public int lTitanium;
    public string planetTouchT;
    public string titaniumTouchT;
    public string treeTouchT;
    public string breaktime;

    public int tree1;
    public int tree2;
    public int tree3;
    public int tree4;
    public int tree5;
    public int tree6;


    public GameObject UIobj;
    public GameObject MoveBtn;
    public GameObject EnergyBtn;
    public GameObject notResText;

    public bool activeFusionPanal = false;

    public bool shipTouch = false;


    public List<GameObject> PlanetList = new List<GameObject>();
    public Dictionary<int, GameObject> D_PlanetList = new Dictionary<int, GameObject>();
    public List<Sprite> EnergyIconList = new List<Sprite>();



    public GameObject SQLManager;
    public float getCountFood;
    public float getCountTitanium;
    public float getCountE;
    public float getCountEE;

    public int maxStoreFood;
    public int maxStoreTitanium;
    int maxStoreE;

    public int maxFood;
    public int maxTitanium;
    public int maxE;

    int treeCount;
    public GameObject getText;
    public GameObject getEnergyText;


    GameObject tempTex;

    string tempString = "";

    public GameObject PostPanalBefore;
    public GameObject PostPanalAfter;

    public GameObject getEspawn;

    void Start()
    {
        treeCount = 0;
    }

    public void callPlanet()
    {
        int PlanetNum = color * 100 + size * 10 + mat;
        UIobj.GetComponent<MainUIfromSQL>().setPlanet(PlanetNum);

    }

    public void callShip()
    {
        UIobj.GetComponent<MainUIfromSQL>().setShip(shipNum);

    }

    public void callTree()
    {
        UIobj.GetComponent<MainUIfromSQL>().setTree(1, tree1);
        UIobj.GetComponent<MainUIfromSQL>().setTree(2, tree2);
        UIobj.GetComponent<MainUIfromSQL>().setTree(3, tree3);
        UIobj.GetComponent<MainUIfromSQL>().setTree(4, tree4);
        UIobj.GetComponent<MainUIfromSQL>().setTree(5, tree5);
        UIobj.GetComponent<MainUIfromSQL>().setTree(6, tree5);

    }

    public void callNeighber()
    {
        UIobj.GetComponent<MainUIfromSQL>().setNeighber();
    }

    public void callStation()
    {
        UIobj.GetComponent<MainUIfromSQL>().setStation();
    }

    public void callPostBox()
    {
        UIobj.GetComponent<MainUIfromSQL>().setPostBox();
    }

    public void getFood(Vector3 textPos)
    {
 
        treeCount = checkTree();
        int canStoreMaxFood = maxStoreFood * treeCount;

        System.DateTime touchTime = System.DateTime.Now;
        string Query = "";
        if(treeTouchT == "0")
        {
            Query = "UPDATE managePlanetTable SET treeTouchT = \"" + touchTime.ToString("yyyy-MM-dd HH:mm:ss") + "\" WHERE rowid = " + rowid;
            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);

            tempTex = Instantiate(getText, textPos, GameObject.Find("PlanetPosition/DragCamera").transform.rotation) as GameObject;
            tempTex.GetComponent<Text>().text = "생산시작";
            return;
        }

        if(cFood >= maxFood)
        {
            cFood = maxFood;
            Query = "UPDATE managePlanetTable SET treeTouchT = \"" + touchTime.ToString("yyyy-MM-dd HH:mm:ss") + "\" WHERE rowid = " + rowid;
            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);

            tempTex = Instantiate(getText, textPos, GameObject.Find("PlanetPosition/DragCamera").transform.rotation) as GameObject;
            tempTex.GetComponent<Text>().text = "MAX";

            return;
        }

        System.DateTime preT = System.DateTime.ParseExact(treeTouchT, "yyyy-MM-dd HH:mm:ss", null);

        System.TimeSpan deff = touchTime - preT;
        int defTime = System.Convert.ToInt32(deff.TotalSeconds);
        int calculateFood = System.Convert.ToInt32(defTime * getCountFood);

        //이후시간, 이전시간 = 1, 같은경우 = 0, 이전,이후 = -1
        int comp = System.DateTime.Compare(touchTime, preT);

        if (comp == 1)
        {
            if (lFood < canStoreMaxFood)
            {
                if (calculateFood < lFood)
                {
                    cFood += calculateFood;
                    lFood -= calculateFood;

                    tempString = calculateFood.ToString();
                }
                else // calculateFood >=lFood
                {
                    cFood += lFood;
                    lFood = 0;

                    tempString = lFood.ToString();
                }
            }
            else // lFood >= maxStoreFood)
            {
                if (calculateFood < canStoreMaxFood)
                {
                    cFood += calculateFood;
                    lFood -= calculateFood;

                    tempString = calculateFood.ToString();
                }
                else //calculateFood >= maxStoreFood && lFood
                {
                    cFood += canStoreMaxFood;
                    lFood -= canStoreMaxFood;

                    tempString = canStoreMaxFood.ToString();
                }
            }

            if(cFood >= maxFood)
            {
                cFood = maxFood;
            }
            if(lFood < 0)
            {
                lFood = 0;
            }

            treeTouchT = touchTime.ToString("yyyy-MM-dd HH:mm:ss");

            tempTex = Instantiate(getText, textPos, GameObject.Find("PlanetPosition/DragCamera").transform.rotation) as GameObject;

            //getText.GetComponent<TextMesh>().text = tempString;
            tempTex.GetComponent<getTextScript>().setText(tempString);

            string tempQuery1 = "UPDATE userTable SET cFood = " + cFood ;
            string tempQuery2 = "UPDATE managePlanetTable SET treeTouchT = \"" + treeTouchT + "\", lFood = " + lFood + " WHERE rowid = " + rowid;
            Debug.Log(tempQuery1);
            Debug.Log(tempQuery2);
            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(tempQuery1);
            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(tempQuery2);

            setVisibleEnergyBtn();

            return;
        }
        else if (comp == 0)
        {
            return;
        }
        else
        {
            treeTouchT = touchTime.ToString("yyyy-MM-dd HH:mm:ss");
            Query = "UPDATE managePlanetTable SET treeTouchT = \"" + treeTouchT + "\" WHERE rowid = " + rowid;
            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);

        }

    }

    int checkTree()
    {
        int a = 0;
        if(tree1 != 0)
        {
            a++;
            if(tree2 != 0)
            {
                a++;

                if (tree3 != 0)
                {
                    a++;

                    if (tree4 != 0)
                    {
                        a++;

                        if (tree5 != 0)
                        {
                            a++;

                            if (tree6 != 0)
                            {
                                a++;
                            }
                        }
                    }
                }
            }
        }
        return a;
    }

    public void getTitanium(Vector3 textPos)
    {
        System.DateTime touchTime = System.DateTime.Now;
        string Query = "";

        if (titaniumTouchT == "0")
        {
            Query = "UPDATE managePlanetTable SET titaniumTouchT = \"" + touchTime.ToString("yyyy-MM-dd HH:mm:ss") + "\" WHERE rowid = " + rowid;
            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);

            tempTex = Instantiate(getText, textPos, GameObject.Find("PlanetPosition/DragCamera").transform.rotation) as GameObject;
            tempTex.GetComponent<getTextScript>().setText("생산시작");

            return;
        }

        if (cTitanium >= maxTitanium)
        {
            cTitanium = maxTitanium;
            Query = "UPDATE managePlanetTable SET treeTouchT = \"" + touchTime.ToString("yyyy-MM-dd HH:mm:ss") + "\" WHERE rowid = " + rowid;
            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);

            tempTex = Instantiate(getText, textPos, GameObject.Find("PlanetPosition/DragCamera").transform.rotation) as GameObject;
            tempTex.GetComponent<getTextScript>().setText("MAX");

            return;
        }


        System.DateTime preT = System.DateTime.ParseExact(titaniumTouchT, "yyyy-MM-dd HH:mm:ss", null);
        System.TimeSpan deff = touchTime - preT;
        int defTime = System.Convert.ToInt32(deff.TotalSeconds);
        int calculateTitanium = System.Convert.ToInt32(defTime * getCountTitanium);

        //이후시간, 이전시간 = 1, 같은경우 = 0, 이전,이후 = -1
        int comp = System.DateTime.Compare(touchTime, preT);

        if (comp == 1)
        {
            if (lTitanium < maxStoreTitanium)
            {
                if (calculateTitanium < lTitanium)
                {
                    cTitanium += calculateTitanium;
                    lTitanium -= calculateTitanium;

                    tempString = calculateTitanium.ToString();

                }
                else // calculateTitanium >=lTitanium
                {
                    cTitanium += lTitanium;
                    lTitanium = 0;

                    tempString = lTitanium.ToString();

                }
            }
            else // lFood >= maxStoreFood)
            {
                if (calculateTitanium < maxStoreTitanium)
                {
                    cTitanium += calculateTitanium;
                    lTitanium -= calculateTitanium;

                    tempString = calculateTitanium.ToString();

                }
                else //calculateFood >= maxStoreFood && lFood
                {
                    cTitanium += maxStoreTitanium;
                    lTitanium -= maxStoreTitanium;

                    tempString = maxStoreTitanium.ToString();

                }
            }

            if (cTitanium > maxTitanium)
            {
                cTitanium = maxTitanium;
            }
            if (lTitanium < 0)
            {
                lTitanium = 0;
            }

            titaniumTouchT = touchTime.ToString("yyyy-MM-dd HH:mm:ss");

            string tempQuery1 = "UPDATE userTable SET cTitanium = " + cTitanium;
            string tempQuery2 = "UPDATE managePlanetTable SET titaniumTouchT = \"" + titaniumTouchT + "\", lTitanium = " + lTitanium + " WHERE rowid = " + rowid;
            Debug.Log(tempQuery1);
            Debug.Log(tempQuery2);

            tempTex = Instantiate(getText, textPos, GameObject.Find("PlanetPosition/DragCamera").transform.rotation) as GameObject;
            tempTex.GetComponent<getTextScript>().setText(tempString);


            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(tempQuery1);
            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(tempQuery2);

            setVisibleEnergyBtn();

            return;
        }
        else if (comp == 0)
        {
            return;
        }
        else
        {
            titaniumTouchT = touchTime.ToString("yyyy-MM-dd HH:mm:ss");
            Query = "UPDATE managePlanetTable SET titaniumTouchT = \"" + titaniumTouchT + "\" WHERE rowid = " + rowid;
            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);
        }
    }

    public void getEnergy()
    {
        SoundManager.Instance().PlaySfx(SoundManager.Instance().uiTouch);
        System.DateTime touchTime = System.DateTime.Now;
        string Query = "";
        if (planetTouchT == "0")
        {
            Query = "UPDATE managePlanetTable SET planetTouchT = \"" + touchTime.ToString("yyyy-MM-dd HH:mm:ss") + "\" WHERE rowid = " + rowid;
            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);

            tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
            tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
            tempTex.GetComponent<getEnergyTextScript>().setText("생산시작");

            return;
        }


        if(lFood ==0 && lTitanium == 0)
        {
            Query = "UPDATE managePlanetTable SET planetTouchT = \"" + touchTime.ToString("yyyy-MM-dd HH:mm:ss") + "\" WHERE rowid = " + rowid;


            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);
            return;
        }

        switch (size)
        {
            case 1:
                maxStoreE = 200;
                break;
            case 2:
                maxStoreE = 400;
                break;
            case 3:
                maxStoreE = 800;
                break;
            case 4:
                maxStoreE = 1600;
                break;
            default:
                maxStoreE = 200;
                break;
        }



        System.DateTime preT = System.DateTime.ParseExact(planetTouchT, "yyyy-MM-dd HH:mm:ss", null);
        System.TimeSpan deff = touchTime - preT;
        int defTime = System.Convert.ToInt32(deff.TotalSeconds);
        int calculateEnergy = System.Convert.ToInt32( defTime * getCountE);

        //이후시간, 이전시간 = 1, 같은경우 = 0, 이전,이후 = -1
        int comp = System.DateTime.Compare(touchTime, preT);

        if (comp == 1)
        {
            string tempQuery1 = "";
            string tempQuery2 = "";


            switch (color)
            {
                case 1: //b

                    if (cBE >= maxE)
                    {
                        cBE = maxE;
                        Query = "UPDATE managePlanetTable SET planetTouchT = \"" + touchTime.ToString("yyyy-MM-dd HH:mm:ss") + "\" WHERE rowid = " + rowid;

                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("MAX");

                        SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);
                        return;
                    }

                    if(calculateEnergy <= maxStoreE)
                    {
                        cBE += calculateEnergy;

                        //tempTex = Instantiate(getEnergyText, Input.mousePosition, Quaternion.identity) as GameObject;
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("+" + calculateEnergy.ToString());


                    }
                    else
                    {
                        cBE += maxStoreE;

                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("+" + maxStoreE.ToString());


                    }


                    if (cBE > maxE)
                    {
                        cBE = maxE;
                    }

                    planetTouchT = touchTime.ToString("yyyy-MM-dd HH:mm:ss");

                    tempQuery1 = "UPDATE userTable SET cBE = " + cBE;
                    tempQuery2 = "UPDATE managePlanetTable SET planetTouchT = \"" + planetTouchT + "\" WHERE rowid = " + rowid;



                    break;

                case 2: //r 
                    if (cRE >= maxE)
                    {
                        cRE = maxE;
                        Query = "UPDATE managePlanetTable SET planetTouchT = \"" + touchTime.ToString("yyyy-MM-dd HH:mm:ss") + "\" WHERE rowid = " + rowid;

                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("MAX");


                        SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);
                        return;
                    }

                    if (calculateEnergy <= maxStoreE)
                    {
                        cRE += calculateEnergy;
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("+" + calculateEnergy.ToString());
                    }
                    else
                    {
                        cRE += maxStoreE;
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("+" + maxStoreE.ToString());
                    }


                    if (cRE > maxE)
                    {
                        cRE = maxE;
                    }

                    planetTouchT = touchTime.ToString("yyyy-MM-dd HH:mm:ss");

                    tempQuery1 = "UPDATE userTable SET cRE = " + cRE;
                    tempQuery2 = "UPDATE managePlanetTable SET planetTouchT = \"" + planetTouchT + "\" WHERE rowid = " + rowid;

                    break;

                case 3: //y
                    if (cYE >= maxE)
                    {
                        cYE = maxE;
                        Query = "UPDATE managePlanetTable SET planetTouchT = \"" + touchTime.ToString("yyyy-MM-dd HH:mm:ss") + "\" WHERE rowid = " + rowid;
                        SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("MAX");
                        return;
                    }

                    if (calculateEnergy <= maxStoreE)
                    {
                        cYE += calculateEnergy;
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("+" + calculateEnergy.ToString());
                    }
                    else
                    {
                        cYE += maxStoreE;
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("+" + maxStoreE.ToString());
                    }


                    if (cYE > maxE)
                    {
                        cYE = maxE;
                    }

                    planetTouchT = touchTime.ToString("yyyy-MM-dd HH:mm:ss");

                    tempQuery1 = "UPDATE userTable SET cYE = " + cYE;
                    tempQuery2 = "UPDATE managePlanetTable SET planetTouchT = \"" + planetTouchT + "\" WHERE rowid = " + rowid;

                    break;

                case 4: //v
                    if (cVE >= maxE)
                    {
                        cVE = maxE;
                        Query = "UPDATE managePlanetTable SET planetTouchT = \"" + touchTime.ToString("yyyy-MM-dd HH:mm:ss") + "\" WHERE rowid = " + rowid;
                        SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("MAX");
                        return;
                    }

                    if (calculateEnergy <= maxStoreE)
                    {
                        cVE += calculateEnergy;
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("+" + calculateEnergy.ToString());
                    }
                    else
                    {
                        cVE += maxStoreE;
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("+" + maxStoreE.ToString());
                    }


                    if (cVE > maxE)
                    {
                        cVE = maxE;
                    }

                    planetTouchT = touchTime.ToString("yyyy-MM-dd HH:mm:ss");

                    tempQuery1 = "UPDATE userTable SET cVE = " + cVE;
                    tempQuery2 = "UPDATE managePlanetTable SET planetTouchT = \"" + planetTouchT + "\" WHERE rowid = " + rowid;
                    break;

                case 5: //g
                    if (cGE >= maxE)
                    {
                        cGE = maxE;
                        Query = "UPDATE managePlanetTable SET planetTouchT = \"" + touchTime.ToString("yyyy-MM-dd HH:mm:ss") + "\" WHERE rowid = " + rowid;
                        SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("MAX");
                        return;
                    }

                    if (calculateEnergy <= maxStoreE)
                    {
                        cGE += calculateEnergy;
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("+" + calculateEnergy.ToString());
                    }
                    else
                    {
                        cGE += maxStoreE;
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("+" + maxStoreE.ToString());
                    }


                    if (cGE > maxE)
                    {
                        cGE = maxE;
                    }

                    planetTouchT = touchTime.ToString("yyyy-MM-dd HH:mm:ss");

                    tempQuery1 = "UPDATE userTable SET cGE = " + cGE;
                    tempQuery2 = "UPDATE managePlanetTable SET planetTouchT = \"" + planetTouchT + "\" WHERE rowid = " + rowid;
                    break;

                case 6: //o
                    if (cOE >= maxE)
                    {
                        cOE = maxE;
                        Query = "UPDATE managePlanetTable SET planetTouchT = \"" + touchTime.ToString("yyyy-MM-dd HH:mm:ss") + "\" WHERE rowid = " + rowid;
                        SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("MAX");
                        return;
                    }

                    if (calculateEnergy <= maxStoreE)
                    {
                        cOE += calculateEnergy;
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("+" + calculateEnergy.ToString());
                    }
                    else
                    {
                        cOE += maxStoreE;
                        tempTex = Instantiate(getEnergyText, getEspawn.transform.localPosition, Quaternion.identity) as GameObject;
                        tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
                        tempTex.GetComponent<getEnergyTextScript>().setText("+" + maxStoreE.ToString());
                    }


                    if (cOE > maxE)
                    {
                        cOE = maxE;
                    }

                    planetTouchT = touchTime.ToString("yyyy-MM-dd HH:mm:ss");

                    tempQuery1 = "UPDATE userTable SET cOE = " + cOE;
                    tempQuery2 = "UPDATE managePlanetTable SET planetTouchT = \"" + planetTouchT + "\" WHERE rowid = " + rowid;
                    break;

                default:
                    return;
            }
            //tempTex = Instantiate(getEnergyText, Input.mousePosition, Quaternion.identity) as GameObject;
            //tempTex.transform.SetParent(GameObject.Find("UI").transform, false);
            //tempTex.GetComponent<getEnergyTextScript>().setText("+5");

            Debug.Log(tempQuery1);
            Debug.Log(tempQuery2);
            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(tempQuery1);
            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(tempQuery2);

            return;
        }
        else if (comp == 0)
        {
            return;
        }
        else
        {
            planetTouchT = touchTime.ToString("yyyy-MM-dd HH:mm:ss");
            Query = "UPDATE managePlanetTable SET planetTouchT = \"" + planetTouchT + "\" WHERE rowid = " + rowid;
            SQLManager.GetComponent<MainSceneSQL>().UpdateQuery(Query);
        }
    }

    public void setVisibleEnergyBtn()
    {
        if(lFood == 0  && lTitanium == 0)
        {
            EnergyBtn.gameObject.SetActive(false);
            notResText.gameObject.SetActive(true);
        }

        if (!position_house)
        {
            EnergyBtn.gameObject.SetActive(false);
        }
    }

    public void setVisibleMoveBtn()
    {
        if(cPlanet == rowid)
        {
            MoveBtn.gameObject.SetActive(false);
        }
    }

    void Update()
    {
            UIobj.GetComponent<MainUIfromSQL>().setUIText();


        if (activeFusionPanal) 
        {
            UIobj.GetComponent<FusionScript>().setText();

        }
    }

    public void setPostPanal()
    {
        GameObject.Find("UI").GetComponent<csScreenPointTouch>().enabled = false;


        PostPanalBefore.gameObject.SetActive(true);
        PostPanalAfter.gameObject.SetActive(false);

    }

    public void confirmInBeforePanal()
    {


        GameObject.Find("GameManager").GetComponent<UnityAds>().ShowRewardedAd();

        PostPanalBefore.gameObject.SetActive(false);
        PostPanalAfter.gameObject.SetActive(true);
    }

    public void cancelInBeforePanal()
    {
        GameObject.Find("UI").GetComponent<csScreenPointTouch>().enabled = true;
        PostPanalBefore.gameObject.SetActive(false);

    }

    public void confirmInAfterPanal()
    {
        GameObject.Find("UI").GetComponent<csScreenPointTouch>().enabled = true;
        PostPanalAfter.gameObject.SetActive(false);

    }


}