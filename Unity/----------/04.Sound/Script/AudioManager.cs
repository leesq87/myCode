using UnityEngine;
using System.Collections;

public class AudioManager : MonoBehaviour {

	static AudioManager _instance = null;
	public static AudioManager Instance(){
		return _instance;
	}

	void Start(){
		if (_instance == null) {
			_instance = this;
		}
	}

	public void PlaySfx(AudioClip clip){
		GetComponent<AudioSource> ().PlayOneShot(clip);
	}




}
