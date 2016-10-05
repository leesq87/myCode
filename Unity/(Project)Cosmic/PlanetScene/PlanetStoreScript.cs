using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;


public class PlanetStoreScript : MonoBehaviour {

    public GameObject SQLManager;

    public GameObject BuildingPanal;
    public GameObject ShipPanal;
    public GameObject CachePanal;

    public List<Sprite> shipList = new List<Sprite>();

    public GameObject lake;

    public Image ShipImage;
    public Text shipMoney;

    public Image stationImg;
    public Image tree1Img;
    public Image tree2Img;
    public Image tree3Img;
    public Image tree4Img;
    public Text stationBtnText;
    public Text tree1BtnText;
    public Text tree2BtnText;
    public Text tree3BtnText;
    public Text tree4BtnText;
    public Sprite notBuy;


    int treeCount = 1;

    public Text storeFood;
    public Text storeTitanium;
    public Text storeEnergy;
    void Start()
    {
        setStoreText();
    }

    public void setStoreText()
    {
        storeFood.text = PlanetSceneSingleTon.Instance.cFood.ToString();
        storeTitanium.text = PlanetSceneSingleTon.Instance.cTitanium.ToString();
        storeEnergy.text = PlanetSceneSingleTon.Instance.cPE.ToString();

    }

    //버튼
    public void Exit()
    {
        GameObject.Find("UI").gameObject.GetComponent<PlanetTouchRay>().enabled = true;
        GameObject.Find("UI/Main/Button").transform.FindChild("SettingBtn").gameObject.SetActive(true);
        GameObject.Find("UI/StorePanal").gameObject.SetActive(false);
    }

    public void activeBuildingPanal()
    {
        BuildingPanal.gameObject.SetActive(true);
        ShipPanal.gameObject.SetActive(false);
        CachePanal.gameObject.SetActive(false);

        setBuildingPanal();
    }

    public void activeShipPanal()
    {
        BuildingPanal.gameObject.SetActive(false);
        ShipPanal.gameObject.SetActive(true);
        CachePanal.gameObject.SetActive(false);
        setShipPanal();
    }

    public void activeCachePanal()
    {
        BuildingPanal.gameObject.SetActive(false);
        ShipPanal.gameObject.SetActive(false);
        CachePanal.gameObject.SetActive(true);
    }

    public void getStation()
    {
        bool station = PlanetSceneSingleTon.Instance.position_house;
        int cTitanium = PlanetSceneSingleTon.Instance.cTitanium;
        string Query = "";
        if (station)
        {
            return;
        }

        if (cTitanium >= 2500)
        {
            Query = "UPDATE managePlanetTable SET position_house = " + 1 + " WHERE User = 1";
            SQLManager.GetComponent<PlanetSceneSQL>().UpdateQuery(Query);

            PlanetSceneSingleTon.Instance.cTitanium -= 2500;
            Query = "UPDATE userTable SET cTitanium = " + PlanetSceneSingleTon.Instance.cTitanium;
            SQLManager.GetComponent<PlanetSceneSQL>().UpdateQuery(Query);

        }
        else
        {
            activeLake();
        }

        setBuildingPanal();
        setStoreText();

    }

    public void getTree1()
    {
        getTree(1);
    }

    public void getTree2()
    {
        getTree(2);
    }

    public void getTree3()
    {
        getTree(3);
    }

    public void getTree4()
    {
        getTree(4);
    }

    void getTree(int treeNum)
    {
        if (tree1BtnText.text == "구매불가")
            return;

        int nowFood = PlanetSceneSingleTon.Instance.cFood;
        int foodCost = System.Convert.ToInt32(tree1BtnText.text);
        string Query = "";
        if (nowFood >= foodCost)
        {
            Debug.Log(PlanetSceneSingleTon.Instance.cFood);
            Query = "UPDATE managePlanetTable SET tree" + treeCount + " = " + treeNum + " Where User = 1 ";
            SQLManager.GetComponent<PlanetSceneSQL>().UpdateQuery(Query);

            PlanetSceneSingleTon.Instance.cFood -= foodCost;
            Query = "UPDATE userTable SET cFood = " + PlanetSceneSingleTon.Instance.cFood;
            SQLManager.GetComponent<PlanetSceneSQL>().UpdateQuery(Query);

        }
        else
        {
            activeLake();
        }

        setBuildingPanal();
        setStoreText();

    }

    void setBuildingPanal()
    {
        bool station = PlanetSceneSingleTon.Instance.position_house;
        int size = PlanetSceneSingleTon.Instance.size;
        int tree1 = PlanetSceneSingleTon.Instance.tree1;
        int tree2 = PlanetSceneSingleTon.Instance.tree2;
        int tree3 = PlanetSceneSingleTon.Instance.tree3;
        int tree4 = PlanetSceneSingleTon.Instance.tree4;
        int tree5 = PlanetSceneSingleTon.Instance.tree5;
        int tree6 = PlanetSceneSingleTon.Instance.tree6;

        if (!station)
        {
            stationBtnText.text = "2500";
        }
        else
        {
            stationImg.sprite = notBuy;
            stationBtnText.text = "구매불가";
        }



        if (tree1 == 0)  //나무없음
        {
            tree1BtnText.text = "25";
            tree2BtnText.text = "25";
            tree3BtnText.text = "25";
            tree4BtnText.text = "25";

        }
        else // 나무1개 이상 있음
        {
            treeCount = 2;
            if (tree2 == 0) // 나무1개만있는경우
            {
                tree1BtnText.text = "50";
                tree2BtnText.text = "50";
                tree3BtnText.text = "50";
                tree4BtnText.text = "50";
            }
            else // 나무 2개이상 있음
            {
                treeCount = 3;
                if (tree3 == 0) //나무2개만 있는경우
                {
                    tree1BtnText.text = "100";
                    tree2BtnText.text = "100";
                    tree3BtnText.text = "100";
                    tree4BtnText.text = "100";
                }
                else //나무3개이상 있음
                {
                    treeCount = 4;
                    if (size == 1) //스몰사이즈 걸러냄
                    {
                        tree1Img.sprite = notBuy;
                        tree2Img.sprite = notBuy;
                        tree3Img.sprite = notBuy;
                        tree4Img.sprite = notBuy;
                        tree1BtnText.text = "구매불가";
                        tree2BtnText.text = "구매불가";
                        tree3BtnText.text = "구매불가";
                        tree4BtnText.text = "구매불가";

                        return;
                    }
                    if (tree4 == 0) //나무 3개만 있는경우
                    {
                        tree1BtnText.text = "200";
                        tree2BtnText.text = "200";
                        tree3BtnText.text = "200";
                        tree4BtnText.text = "200";
                    }
                    else //나무4개이상 있음
                    {
                        treeCount = 5;
                        if (size == 2) // 미디움사이즈 걸러냄
                        {
                            tree1Img.sprite = notBuy;
                            tree2Img.sprite = notBuy;
                            tree3Img.sprite = notBuy;
                            tree4Img.sprite = notBuy;
                            tree1BtnText.text = "구매불가";
                            tree2BtnText.text = "구매불가";
                            tree3BtnText.text = "구매불가";
                            tree4BtnText.text = "구매불가";
                            return;
                        }
                        if (tree5 == 0) //나무4개만 있는경우
                        {
                            tree1BtnText.text = "400";
                            tree2BtnText.text = "400";
                            tree3BtnText.text = "400";
                            tree4BtnText.text = "400";
                        }
                        else // 나무5개이상 있음
                        {
                            treeCount = 6;
                            if (size == 3) //빅사이즈 걸러냄 
                            {
                                tree1Img.sprite = notBuy;
                                tree2Img.sprite = notBuy;
                                tree3Img.sprite = notBuy;
                                tree4Img.sprite = notBuy;
                                tree1BtnText.text = "구매불가";
                                tree2BtnText.text = "구매불가";
                                tree3BtnText.text = "구매불가";
                                tree4BtnText.text = "구매불가";
                                return;
                            }
                            if (tree6 == 0) //나무 5개만 있는경우
                            {
                                tree1BtnText.text = "800";
                                tree2BtnText.text = "800";
                                tree3BtnText.text = "800";
                                tree4BtnText.text = "800";
                            }
                            else //나무 6개이상 있음
                            {
                                treeCount = 7;
                                tree1Img.sprite = notBuy;
                                tree2Img.sprite = notBuy;
                                tree3Img.sprite = notBuy;
                                tree4Img.sprite = notBuy;
                                tree1BtnText.text = "구매불가";
                                tree2BtnText.text = "구매불가";
                                tree3BtnText.text = "구매불가";
                                tree4BtnText.text = "구매불가";
                                return;
                            }
                        }
                    }
                }
            }
        }


    }

    public void getShip()
    {

        int nowShipNum = PlanetSceneSingleTon.Instance.shipNum;
        int nowTitanium = PlanetSceneSingleTon.Instance.cTitanium;
        string Query = "";


        switch (nowShipNum)
        {
            case 1:
                if (nowTitanium < 9999)
                {
                    activeLake();
                }
                else
                {
                    PlanetSceneSingleTon.Instance.cTitanium -= 9999;
                    PlanetSceneSingleTon.Instance.shipNum++;

                    Query = "UPDATE userTable SET cTitanium = " + PlanetSceneSingleTon.Instance.cTitanium + ", shipNum = " + PlanetSceneSingleTon.Instance.shipNum;
                    SQLManager.GetComponent<PlanetSceneSQL>().UpdateQuery(Query);

                }
                break;

            case 2:
                if (nowTitanium < 12900)
                {
                    activeLake();
                }
                else
                {
                    PlanetSceneSingleTon.Instance.cTitanium -= 12900;
                    PlanetSceneSingleTon.Instance.shipNum++;

                    Query = "UPDATE userTable SET cTitanium = " + PlanetSceneSingleTon.Instance.cTitanium + ", shipNum = " + PlanetSceneSingleTon.Instance.shipNum;
                    SQLManager.GetComponent<PlanetSceneSQL>().UpdateQuery(Query);
                }
                break;

            case 3:
                if (nowTitanium < 15900)
                {
                    activeLake();
                }
                else
                {
                    PlanetSceneSingleTon.Instance.cTitanium -= 15900;
                    PlanetSceneSingleTon.Instance.shipNum++;

                    Query = "UPDATE userTable SET cTitanium = " + PlanetSceneSingleTon.Instance.cTitanium + ", shipNum = " + PlanetSceneSingleTon.Instance.shipNum;
                    SQLManager.GetComponent<PlanetSceneSQL>().UpdateQuery(Query);
                }
                break;

            case 4:
                if (nowTitanium < 20000)
                {
                    activeLake();
                }
                else
                {
                    PlanetSceneSingleTon.Instance.cTitanium -= 20000;
                    PlanetSceneSingleTon.Instance.shipNum++;

                    Query = "UPDATE userTable SET cTitanium = " + PlanetSceneSingleTon.Instance.cTitanium + ", shipNum = " + PlanetSceneSingleTon.Instance.shipNum;
                    SQLManager.GetComponent<PlanetSceneSQL>().UpdateQuery(Query);

                }
                break;


            default:
                break;

        }

        setShipPanal();
        setStoreText();


    }

    void activeLake()
    {
        lake.gameObject.SetActive(true);
        lakescript.ActiveFalseTime = 0;
    }

    void setShipPanal()
    {
        int tempShip = PlanetSceneSingleTon.Instance.shipNum;
        switch (tempShip)
        {
            case 1:
                ShipImage.sprite = shipList[0];
                shipMoney.text = "9999";

                //GameObject.Find("UI/StorePanal/ViewPanal/ShipsPanal/Panal/Image/ImgNot").gameObject.SetActive(false);
                break;

            case 2:
                ShipImage.sprite = shipList[1];
                shipMoney.text = "12900";
                //GameObject.Find("UI/StorePanal/ViewPanal/ShipsPanal/Panal/Image/ImgNot").gameObject.SetActive(false);
                break;

            case 3:
                ShipImage.sprite = shipList[2];
                shipMoney.text = "15900";
                //GameObject.Find("UI/StorePanal/ViewPanal/ShipsPanal/Panal/Image/ImgNot").gameObject.SetActive(false);
                break;

            case 4:
                ShipImage.sprite = shipList[3];
                shipMoney.text = "20000";
                //GameObject.Find("UI/StorePanal/ViewPanal/ShipsPanal/Panal/Image/ImgNot").gameObject.SetActive(false);
                break;

            case 5:
                ShipImage.sprite = shipList[4];
                shipMoney.text = "구매불가";
                //GameObject.Find("UI/StorePanal/ViewPanal/ShipsPanal/Panal/Image/ImgNot").gameObject.SetActive(true);
                break;

            default:
                shipMoney.text = "구매불가";
                //GameObject.Find("UI/StorePanal/ViewPanal/ShipsPanal/Panal/Image/ImgNot").gameObject.SetActive(true);
                break;

        }

    }

    void Update()
    {
        setStoreText();
    }

}

