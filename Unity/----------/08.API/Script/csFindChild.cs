using UnityEngine;
using System.Collections;

public class csFindChild : MonoBehaviour {

	public Transform[] myChilds;

	void Start(){
		int randomSeedS;
		randomSeedS = (int)System.DateTime.Now.Ticks;
		Random.seed = randomSeedS;

		myChilds = GameObject.Find ("SpawnPoint").GetComponentsInChildren<Transform> ();

		int idx = Random.Range (1, myChilds.Length);

		Debug.Log ("SpawnPoint.length :" + myChilds.Length);
		Debug.Log ("Random.Range : " + idx);


		for (int i = 0; i < myChilds.Length; i++) {
			Debug.Log (myChilds [i].gameObject.name);
		}
	}




}
