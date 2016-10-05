using UnityEngine;
using System.Collections;

public class csMove1 : MonoBehaviour {

	// Use this for initialization
	void Start () {

		//트랜스폼 포션 셋팅 : 이동
		//해당 Vector의 값으로 이동하여 위치하게 됨
		this.transform.position = new Vector3(0.0f,0.5f,0.0f);

		//이동
		//현재 위에서 주어진 값만큼 이동
		this.transform.Translate(new Vector3(0.0f,0.0f,1.0f));

	}
	

}
