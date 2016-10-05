using UnityEngine;
using System.Collections;

public class csPlay : MonoBehaviour {

	void OnCollisionEnter(Collision collision){
		GetComponent<AudioSource> ().Play ();

	}

}
