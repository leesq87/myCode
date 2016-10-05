using UnityEngine;
using System.Collections;

public class csPlayOneShot : MonoBehaviour {

	public AudioClip clip;

	void OnCollisionEnter(Collision collision){
		GetComponent<AudioSource> ().PlayOneShot (clip);
		GetComponent<AudioSource> ().PlayOneShot (clip, 0.8f);
	}



}
