using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System.Collections.Generic;

public class PlanetUIFromSQL : MonoBehaviour {

    public GameObject haveFood;
    public GameObject haveTitanium;
    public GameObject havePEEnergy;
    public GameObject PlanetName;
    public GameObject leftFood;
    public GameObject leftTitanium;

    public GameObject getEnergyBtn;

    public void setUIText()
    {
        haveFood.GetComponent<Text>().text = PlanetSceneSingleTon.Instance.cFood.ToString();
        haveTitanium.GetComponent<Text>().text = PlanetSceneSingleTon.Instance.cTitanium.ToString();
        havePEEnergy.GetComponent<Text>().text = PlanetSceneSingleTon.Instance.cPE.ToString();
        PlanetName.GetComponent<Text>().text = PlanetSceneSingleTon.Instance.pName.ToString();
        leftFood.GetComponent<Text>().text = PlanetSceneSingleTon.Instance.lFood.ToString();
        leftTitanium.GetComponent<Text>().text = PlanetSceneSingleTon.Instance.lTitanium.ToString();
        getEnergyBtn.GetComponent<Image>().sprite = PlanetSceneSingleTon.Instance.EnergyIconList[PlanetSceneSingleTon.Instance.color - 1];
    }

}
