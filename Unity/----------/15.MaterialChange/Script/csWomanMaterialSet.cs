using UnityEngine;
using System.Collections;

public class csWomanMaterialSet : MonoBehaviour {

	//for Woman
	public Material[] _M_Eyes;
	public Material[] _M_Hair1;
	public Material[] _M_Hair2;
	public Material[] _M_Top1;
	public Material[] _M_Top2;
	public Material[] _M_Pants1;
	public Material[] _M_Pants2;
	public Material[] _M_Shoes1;
	public Material[] _M_Shoes2;


	public GameObject _Eyes;
	public GameObject _Hair1;
	public GameObject _Hair2;
	public GameObject _Top1;
	public GameObject _Top2;
	public GameObject _Pants1;
	public GameObject _Pants2;
	public GameObject _Shoes1;
	public GameObject _Shoes2;


	void Start(){
		CharMaterialSet (_Eyes, _M_Eyes [1]);
		CharMaterialSet (_Hair1, _M_Hair1 [1]);
		CharMaterialSet (_Hair2, _M_Hair2 [1]);
		CharMaterialSet (_Top1, _M_Top1 [1]);
		CharMaterialSet (_Top2, _M_Top2 [1]);
		CharMaterialSet (_Pants1, _M_Pants1 [1]);
		CharMaterialSet (_Pants2, _M_Pants2 [1]);
		CharMaterialSet (_Shoes1, _M_Shoes1 [1]);
		CharMaterialSet (_Shoes2, _M_Shoes2 [1]);

	}

	void CharMaterialSet(GameObject obj, Material mat){

		obj.GetComponent<Renderer> ().material = mat;
	}


}
