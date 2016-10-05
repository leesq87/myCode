using UnityEngine;
using System.Collections;

public class csMecanim2 : MonoBehaviour {

	private Animator anim;

	void Start(){
		anim = GetComponent<Animator> ();
	}

	void FixedUpdate(){
		float h = Input.GetAxis ("Horizontal");
		float v = Input.GetAxis ("Vertical");

		anim.SetFloat ("speed", v);
		anim.SetFloat ("direction", h);
	}



}
