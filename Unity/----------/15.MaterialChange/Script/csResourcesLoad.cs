using UnityEngine;
using System.Collections;

public class csResourcesLoad : MonoBehaviour {

	string[] _M_Eyes = {
		"Images/female_eyes_blue",
		"Images/female_eyes_brown",
		"Images/female_eyes_green"
	};

	string[] _M_Hair1 = {
		"Images/female_hair-1_brown",
		"Images/female_hair-1_red",
		"Images/female_hair-1_yellow"
	};

	string[] _M_Pants1 = {
		"Images/female_pants-1_blue",
		"Images/female_pants-1_dark",
		"Images/female_pants-1_green"
	};

	string[] _M_Top1 = {
		"Images/female_top-1_blue",
		"Images/female_top-1_green",
		"Images/female_top-1_pink"
	};


	public GameObject _Eyes;
	public GameObject _Hair;
	public GameObject _Pants1;
	public GameObject _Top1;

	int nEyes = 0;
	int nHair = 0;
	int nPants = 0;
	int nTop = 0;



	public void ChangeEyes(){
		nEyes++;

		if (nEyes > _M_Eyes.Length - 1) {
			nEyes = 0;
		}

		CharMaterialSet (_Eyes, _M_Eyes[nEyes]);
	}

	public void ChangeHair(){
		nHair++;

		if (nHair > _M_Hair1.Length - 1) {
			nHair = 0;
		}

		CharMaterialSet (_Hair, _M_Hair1[nHair]);
	}

	public void ChangePants(){
		nPants++;

		if (nPants > _M_Pants1.Length - 1) {
			nPants = 0;
		}

		CharMaterialSet (_Pants1, _M_Pants1[nPants]);
	}
	public void ChangeTop(){
		nTop++;

		if (nTop > _M_Top1.Length - 1) {
			nTop = 0;
		}

		CharMaterialSet (_Top1, _M_Top1[nTop]);
	}

	void CharMaterialSet(GameObject obj, string mat){
		obj.GetComponent<Renderer> ().material.mainTexture = Resources.Load (mat) as Texture;
	}
}
