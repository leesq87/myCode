using UnityEngine;
using System.Collections;

public class csPlayClipAtPoint : MonoBehaviour {

	float speed = 20.0f;

	public Transform box2;
	public AudioClip myClip;


	void Update(){
		float v = Input.GetAxis ("Vertical");

		v = v * speed * Time.deltaTime;

		box2.Translate (Vector3.forward * v);

		if(Input.GetButtonDown("Fire1")){
			AudioSource.PlayClipAtPoint (myClip, box2.position);
		}
	}




}
