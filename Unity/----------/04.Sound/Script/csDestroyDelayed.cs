using UnityEngine;
using System.Collections;

public class csDestroyDelayed : MonoBehaviour {

	private AudioSource myAudio;

	void Start(){
		myAudio = GetComponent<AudioSource> ();
	}

	void OnCollisionEnter(Collision collision){
		myAudio.Play ();

		Destroy (this.gameObject, myAudio.clip.length);
	}


}
