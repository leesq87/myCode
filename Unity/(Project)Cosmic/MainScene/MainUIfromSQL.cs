using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System.Collections.Generic;


public class MainUIfromSQL : MonoBehaviour
{
    public GameObject haveFood;
    public GameObject haveTitanium;
    public GameObject havePEEnergy;
    public GameObject PlanetName;
    public GameObject leftFood;
    public GameObject leftTitanium;
    public GameObject singleTon;
    public GameObject PlanetList;
    public GameObject PlanetPosition;

    public GameObject getEnergyBtn;

    GameObject Pla;

    public RuntimeAnimatorController cont;


    public void setUIText()
    {
        haveFood.GetComponent<Text>().text = singleTon.GetComponent<MainSingleTon>().cFood + "";
        haveTitanium.GetComponent<Text>().text = singleTon.GetComponent<MainSingleTon>().cTitanium + "";
        havePEEnergy.GetComponent<Text>().text = singleTon.GetComponent<MainSingleTon>().cPE + "";
        PlanetName.GetComponent<Text>().text = singleTon.GetComponent<MainSingleTon>().pName;
        leftFood.GetComponent<Text>().text = singleTon.GetComponent<MainSingleTon>().lFood + "";
        leftTitanium.GetComponent<Text>().text = singleTon.GetComponent<MainSingleTon>().lTitanium + "";
        getEnergyBtn.GetComponent<Image>().sprite = MainSingleTon.Instance.EnergyIconList[MainSingleTon.Instance.color -1];

    }

    public void setPlanet(int Num)
    {
        if (PlanetPosition.transform.childCount == 1)
        {
            Pla = Instantiate(MainSingleTon.Instance.D_PlanetList[Num], PlanetPosition.transform.position, PlanetPosition.transform.rotation) as GameObject;
            Pla.name = "death_planet";
            Pla.transform.localScale = new Vector3(0.35f, 0.35f, 0.35f);
            Pla.transform.parent = PlanetPosition.transform;
            Camera.main.transform.parent = PlanetPosition.transform.FindChild("DragCamera").transform;
            Destroy(Pla.GetComponent<Rigidbody>());
            //            Destroy(Pla.GetComponent<SphereCollider>();

            Pla.gameObject.GetComponent<SphereCollider>().isTrigger = false;
            Pla.transform.FindChild("PC/astronaut").gameObject.tag = "Player";
            Pla.transform.FindChild("PC").gameObject.tag = "Player";

            Pla.transform.FindChild("PC/astronaut").gameObject.transform.localPosition = new Vector3(0f, 0f, 0f);
            //Pla.transform.FindChild("PC/astronaut").gameObject.transform.rotation( new Vector3(0f, 0f, 0f));
            //Pla.transform.FindChild("PC/astronaut").gameObject.transform.position = new Vector3(0f, 0f, 0f);

            Pla.transform.FindChild("PC/astronaut").gameObject.AddComponent<BoxCollider>();
            Pla.transform.FindChild("PC/astronaut").gameObject.GetComponent<BoxCollider>().center = new Vector3(0f, 0.7f, 0f);
            Pla.transform.FindChild("PC/astronaut").gameObject.GetComponent<BoxCollider>().size = new Vector3(0.9f, 1.5f, 1f);


            Pla.gameObject.AddComponent<GravityAttractor>();
            Pla.transform.FindChild("PC").gameObject.AddComponent<GravityBody>();
            Pla.transform.FindChild("PC").gameObject.GetComponent<GravityBody>().attractor = Pla.gameObject.GetComponent<GravityAttractor>();
            Pla.transform.FindChild("PC").gameObject.AddComponent<PlayerController>();

            Pla.transform.FindChild("PC").gameObject.GetComponent<Animator>().runtimeAnimatorController = cont;
            Pla.transform.FindChild("PC").gameObject.AddComponent<Rigidbody>();
            Pla.transform.FindChild("PC").gameObject.AddComponent<CapsuleCollider>();
            Pla.transform.FindChild("PC").gameObject.GetComponent<CapsuleCollider>().center = new Vector3(0f, 1f, 0f);
            Pla.transform.FindChild("PC").gameObject.GetComponent<CapsuleCollider>().height = 2f;

            //Pla.transform.FindChild("PC").gameObject.GetComponent<Rigidbody>().freezeRotation;

            Pla.transform.FindChild("PC").gameObject.GetComponent<PlayerController>().anim = Pla.transform.FindChild("PC").gameObject.GetComponent<Animator>();



        }
    }

    public void setShip(int num)
    {
        switch (num)
        {
            case 1:
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_1").gameObject.SetActive(true);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_2").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_3").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_4").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_5").gameObject.SetActive(false);

                break;

            case 2:
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_1").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_2").gameObject.SetActive(true);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_3").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_4").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_5").gameObject.SetActive(false);

                break;

            case 3:
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_1").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_2").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_3").gameObject.SetActive(true);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_4").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_5").gameObject.SetActive(false);

                break;

            case 4:
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_1").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_2").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_3").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_4").gameObject.SetActive(true);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_5").gameObject.SetActive(false);

                break;

            case 5:
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_1").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_2").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_3").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_4").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_5").gameObject.SetActive(true);

                break;

            default:
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_1").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_2").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_3").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_4").gameObject.SetActive(false);
                GameObject.Find("PlanetPosition/death_planet/Ship/Ship_5").gameObject.SetActive(false);

                break;

        }

    }

    public void setTree(int TreeCount, int TreeNum)
    {
        string stringTree = "PlanetPosition/death_planet/Tree_" + TreeCount;

        if (GameObject.Find(stringTree) == null)
        {
            return;

        }
        switch (TreeNum)
        {
            case 0:
                GameObject.Find(stringTree + "/Pinetree_" + TreeCount).gameObject.SetActive(false);
                GameObject.Find(stringTree + "/Springtree_" + TreeCount).gameObject.SetActive(false);
                GameObject.Find(stringTree + "/Mapletree_" + TreeCount).gameObject.SetActive(false);
                GameObject.Find(stringTree + "/Wintertree_" + TreeCount).gameObject.SetActive(false);
                break;

            case 1:
                GameObject.Find(stringTree + "/Pinetree_" + TreeCount).gameObject.SetActive(true);
                GameObject.Find(stringTree + "/Springtree_" + TreeCount).gameObject.SetActive(false);
                GameObject.Find(stringTree + "/Mapletree_" + TreeCount).gameObject.SetActive(false);
                GameObject.Find(stringTree + "/Wintertree_" + TreeCount).gameObject.SetActive(false);

                break;

            case 2:
                GameObject.Find(stringTree + "/Pinetree_" + TreeCount).gameObject.SetActive(false);
                GameObject.Find(stringTree + "/Springtree_" + TreeCount).gameObject.SetActive(true);
                GameObject.Find(stringTree + "/Mapletree_" + TreeCount).gameObject.SetActive(false);
                GameObject.Find(stringTree + "/Wintertree_" + TreeCount).gameObject.SetActive(false);

                break;

            case 3:
                GameObject.Find(stringTree + "/Pinetree_" + TreeCount).gameObject.SetActive(false);
                GameObject.Find(stringTree + "/Springtree_" + TreeCount).gameObject.SetActive(false);
                GameObject.Find(stringTree + "/Mapletree_" + TreeCount).gameObject.SetActive(true);
                GameObject.Find(stringTree + "/Wintertree_" + TreeCount).gameObject.SetActive(false);

                break;

            case 4:
                GameObject.Find(stringTree + "/Pinetree_" + TreeCount).gameObject.SetActive(false);
                GameObject.Find(stringTree + "/Springtree_" + TreeCount).gameObject.SetActive(false);
                GameObject.Find(stringTree + "/Mapletree_" + TreeCount).gameObject.SetActive(false);
                GameObject.Find(stringTree + "/Wintertree_" + TreeCount).gameObject.SetActive(true);

                break;

            default:
                break;

        }

    }

    public void setNeighber()
    {
        if(MainSingleTon.Instance.neighbor == 0)
        {
            GameObject.Find("PlanetPosition/death_planet/Ship_Neighbor").gameObject.SetActive(false);
            GameObject.Find("PlanetPosition/death_planet/Neighbor").gameObject.SetActive(false);
        }
        else
        {
            GameObject.Find("PlanetPosition/death_planet/Ship_Neighbor").gameObject.SetActive(true);
            GameObject.Find("PlanetPosition/death_planet/Neighbor").gameObject.SetActive(true);

        }
    }

    public void setStation()
    {
        if (MainSingleTon.Instance.position_house)
        {
            GameObject.Find("PlanetPosition/death_planet/Spacestation").gameObject.SetActive(true);
        }
        else
        {
            GameObject.Find("PlanetPosition/death_planet/Spacestation").gameObject.SetActive(false);

        }
    }

    public void setPostBox()
    {
        if (MainSingleTon.Instance.cPlanet == MainSingleTon.Instance.rowid)
        {
            GameObject.Find("PlanetPosition/death_planet/Postbox").gameObject.SetActive(true);
            if (!GameObject.Find("PlanetPosition/death_planet/Postbox").GetComponent<BoxCollider>())
            {
                GameObject.Find("PlanetPosition/death_planet/Postbox").AddComponent<BoxCollider>();
                GameObject.Find("PlanetPosition/death_planet/Postbox").GetComponent<BoxCollider>().size = new Vector3(0.5f, 2f, 1f);
                GameObject.Find("PlanetPosition/death_planet/Postbox").GetComponent<BoxCollider>().center = new Vector3(0f, 1.5f, -0.5f);
            }

        }
        else
        {
            GameObject.Find("PlanetPosition/death_planet/Postbox").gameObject.SetActive(false);
        }
    }

}
