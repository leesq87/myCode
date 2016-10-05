using UnityEngine;
using System.Collections;

public class csCheck3DSound : MonoBehaviour {

	float speed = 20.0f;

	void Update(){
		float v = Input.GetAxis ("Vertical");

		v = v * speed * Time.deltaTime;

		transform.Translate (Vector3.forward * v);

		if(Input.GetButtonDown("Fire1")){
			GetComponent<AudioSource> ().Play ();
		}
	}





}
