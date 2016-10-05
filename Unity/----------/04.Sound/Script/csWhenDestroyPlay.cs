using UnityEngine;
using System.Collections;

public class csWhenDestroyPlay : MonoBehaviour {

	void OnCollisionEnter(Collision collision){
		GetComponent<AudioSource> ().Play ();

		Destroy (this.gameObject);
	}



}
