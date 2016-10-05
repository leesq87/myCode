using UnityEngine;
using System.Collections;

public class csDynamicChange : MonoBehaviour {

	public Material[] _M_Eyes;
	public Material[] _M_Hair1;
	public Material[] _M_Pants1;
	public Material[] _M_Top1;

	public GameObject _Eyes;
	public GameObject _Hair1;
	public GameObject _Pants1;
	public GameObject _Top1;

	int nEyes =0;
	int nHair=0;
	int nPants=0;
	int nTop =0;


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

		CharMaterialSet (_Hair1, _M_Hair1[nHair]);
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


	void CharMaterialSet(GameObject obj, Material mat){
		obj.GetComponent<Renderer> ().material = mat;
	}



}
