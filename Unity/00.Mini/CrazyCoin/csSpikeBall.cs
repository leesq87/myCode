using UnityEngine;
using System.Collections;

public class csSpikeBall : MonoBehaviour {

	void OnTriggerEnter(Collider other){
		other.gameObject.SendMessage ("ApplyDamage", 10);

		Destroy (gameObject);
	}



}
