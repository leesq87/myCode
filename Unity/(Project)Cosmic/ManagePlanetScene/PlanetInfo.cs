using UnityEngine;
using UnityEngine.EventSystems;
using System.Linq;
using System.Collections;
using System.Collections.Generic;

public class PlanetInfo : MonoBehaviour {

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

    public int tree1;
    public int tree2;
    public int tree3;
    public int tree4;
    public int tree5;
    public int tree6;


    public void Start()
    {
        if (!user)
        {
            this.transform.FindChild("Postbox").gameObject.SetActive(false);
            this.transform.FindChild("PC").gameObject.SetActive(false);
            this.transform.FindChild("Ship").gameObject.SetActive(false);
        }

        this.transform.FindChild("Zoo").gameObject.SetActive(false);

        setStation(position_house);
        setNeighbor(neighbor);

        setTree(1,tree1);
        setTree(2,tree2);
        setTree(3, tree3);
        setTree(4, tree4);
        setTree(5, tree5);
        setTree(6, tree6);


    }

    void setNeighbor(int num)
    {
        if (num == 0)
        {
            this.transform.FindChild("Ship_Neighbor").gameObject.SetActive(false);
            this.transform.FindChild("Neighbor").gameObject.SetActive(false);
        }
        else
        {
            this.transform.FindChild("Ship_Neighbor").gameObject.SetActive(true);
            this.transform.FindChild("Neighbor").gameObject.SetActive(true);
        }
    }

    void setStation(bool station)
    {
        if (station)
        {
            this.transform.FindChild("Spacestation").gameObject.SetActive(true);
        }
        else
        {
            this.transform.FindChild("Spacestation").gameObject.SetActive(false);

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
        string stringTree = "Tree_" + TreeCount;

        if (this.transform.FindChild(stringTree) == null)
        {
            return;

        }
        switch (TreeNum)
        {
            case 0:
                this.transform.FindChild(stringTree + "/Pinetree_" + TreeCount).gameObject.SetActive(false);
                this.transform.FindChild(stringTree + "/Springtree_" + TreeCount).gameObject.SetActive(false);
                this.transform.FindChild(stringTree + "/Mapletree_" + TreeCount).gameObject.SetActive(false);
                this.transform.FindChild(stringTree + "/Wintertree_" + TreeCount).gameObject.SetActive(false);
                break;

            case 1:
                this.transform.FindChild(stringTree + "/Pinetree_" + TreeCount).gameObject.SetActive(true);
                this.transform.FindChild(stringTree + "/Springtree_" + TreeCount).gameObject.SetActive(false);
                this.transform.FindChild(stringTree + "/Mapletree_" + TreeCount).gameObject.SetActive(false);
                this.transform.FindChild(stringTree + "/Wintertree_" + TreeCount).gameObject.SetActive(false);

                break;

            case 2:
                this.transform.FindChild(stringTree + "/Pinetree_" + TreeCount).gameObject.SetActive(false);
                this.transform.FindChild(stringTree + "/Springtree_" + TreeCount).gameObject.SetActive(true);
                this.transform.FindChild(stringTree + "/Mapletree_" + TreeCount).gameObject.SetActive(false);
                this.transform.FindChild(stringTree + "/Wintertree_" + TreeCount).gameObject.SetActive(false);

                break;

            case 3:
                this.transform.FindChild(stringTree + "/Pinetree_" + TreeCount).gameObject.SetActive(false);
                this.transform.FindChild(stringTree + "/Springtree_" + TreeCount).gameObject.SetActive(false);
                this.transform.FindChild(stringTree + "/Mapletree_" + TreeCount).gameObject.SetActive(true);
                this.transform.FindChild(stringTree + "/Wintertree_" + TreeCount).gameObject.SetActive(false);

                break;

            case 4:
                this.transform.FindChild(stringTree + "/Pinetree_" + TreeCount).gameObject.SetActive(false);
                this.transform.FindChild(stringTree + "/Springtree_" + TreeCount).gameObject.SetActive(false);
                this.transform.FindChild(stringTree + "/Mapletree_" + TreeCount).gameObject.SetActive(false);
                this.transform.FindChild(stringTree + "/Wintertree_" + TreeCount).gameObject.SetActive(true);

                break;

            default:
                break;

        }

    }

}
