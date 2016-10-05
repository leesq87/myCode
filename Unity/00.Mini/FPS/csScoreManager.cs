using UnityEngine;
using System.Collections;

public class csScoreManager : MonoBehaviour {

	static csScoreManager _instance = null;
	public static csScoreManager Instance(){
		return _instance;
	}

	void Start(){
		if (_instance == null) {
			_instance = this;

		}
		LoadBestScore ();
	}


	int _bestScore = 0;
	int _myScore = 0;

	public int bestScore {
		get {
			return _bestScore;
		}
	}

	public int myScore {
		get {
			return _myScore;
		}
		set {
			_myScore = value;
			if (_myScore > _bestScore) {
				_bestScore = _myScore;
				SaveBsetScore ();
			}
		}
	}


	void SaveBsetScore(){
		PlayerPrefs.SetInt ("Best Score",_bestScore);

	}

	void LoadBestScore(){
		_bestScore = PlayerPrefs.GetInt ("Best Score", 0);
	}





}
