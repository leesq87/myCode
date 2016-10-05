using UnityEngine;
using System.Collections;

public class SoundManager : MonoBehaviour {
	// make singletone
	public static SoundManager instance;
	public AudioClip sndExplosion;
	AudioSource myAudio;

	void Awake(){
		if(SoundManager.instance ==null){
			SoundManager.instance = this;
		}
	}

	void Start(){
		myAudio = GetComponent<AudioSource> ();
	}

	void Update(){

	}

	public void PlaySound(){
		myAudio.PlayOneShot (sndExplosion);
	}



}
