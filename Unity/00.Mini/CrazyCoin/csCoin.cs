using UnityEngine;
using System.Collections;

public class csCoin : MonoBehaviour {

	void OnTriggerEnter(Collider other){
		other.gameObject.SendMessage ("CatchCoin", 1);
		Destroy (gameObject);
	}


}
