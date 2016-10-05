using UnityEngine;
using System.Collections;
using UnityEngine.EventSystems;
using UnityStandardAssets.Utility;

public class CameraManager : MonoBehaviour, IBeginDragHandler, IDragHandler, IEndDragHandler {

	public float dragRate = 40;

	public GameObject rotateBase;
	public GameObject mainCamara;

	bool isWhite;

	Quaternion rotateBaseRotation;

	bool setTacticalView = false;

	void Start()
	{
		//Debug.Log("DragScriptStart");
		isWhite = PhotonNetwork.isMasterClient;
	}

	void Update()
	{
		TacticalViewUpdate ();
	}

	public void OnBeginDrag(PointerEventData eventData)
	{
		
		//Debug.Log("OnBeginDrag");
	}
	public void OnDrag(PointerEventData eventData)
	{
		if (setTacticalView) 
		{
			return;
		}

		//Debug.Log("OnDrag");
		rotateBase.transform.Rotate(new Vector3(-eventData.delta.y/dragRate, eventData.delta.x/dragRate,0 ));

		if (isWhite) 
		{
			if (rotateBase.transform.rotation.eulerAngles.y < 270.0f && rotateBase.transform.rotation.eulerAngles.y > 180.0f) 
			{
				rotateBase.transform.rotation = Quaternion.Euler (0, 270.0f, 0);
			}
			if (rotateBase.transform.rotation.eulerAngles.y > 90.0f && rotateBase.transform.rotation.eulerAngles.y < 180.0f) 
			{
				rotateBase.transform.rotation = Quaternion.Euler (0, 90.0f, 0);
			}
		} 
		else 
		{
			if (rotateBase.transform.rotation.eulerAngles.y > 270.0f && rotateBase.transform.rotation.eulerAngles.y > 180.0f) 
			{
				rotateBase.transform.rotation = Quaternion.Euler (0, 270.0f, 0);
			}
			if (rotateBase.transform.rotation.eulerAngles.y < 90.0f && rotateBase.transform.rotation.eulerAngles.y > 0.0f) 
			{
				rotateBase.transform.rotation = Quaternion.Euler (0, 90.0f, 0);
			}
		}
	}
	public void OnEndDrag(PointerEventData eventData)
	{
		//Debug.Log("OnDragEnd");
	}

	/// <summary>
	/// 전술뷰 변경 함수
	/// setTacticalView : 값에 따라 상태 변경
	/// </summary>
	void TacticalViewUpdate()
	{
		if (setTacticalView)
		{
			if (mainCamara.GetComponent<SmoothFollow> ().distance > 0.001f)
			{
				mainCamara.GetComponent<SmoothFollow> ().distance -= (Time.deltaTime * 10);

				if (isWhite)
				{
					rotateBase.transform.rotation = Quaternion.Euler (0, 0, 0);
				}
				else
				{
					rotateBase.transform.rotation = Quaternion.Euler (0, 180.0f, 0);
				}

				if (mainCamara.GetComponent<SmoothFollow> ().distance < 0.001f)
				{
					mainCamara.GetComponent<SmoothFollow> ().distance = 0.001f;
				}
			}
			mainCamara.GetComponent<SmoothFollow> ().height = 25.0f;
		}
		else
		{
			if (mainCamara.GetComponent<SmoothFollow> ().distance < 16.0f)
			{
				mainCamara.GetComponent<SmoothFollow> ().distance += (Time.deltaTime * 10);
				rotateBase.transform.rotation = rotateBaseRotation;
			}
			mainCamara.GetComponent<SmoothFollow> ().height = 16.0f;
		}
	}

	public void BtnTacticalView()
	{
		if (setTacticalView)
		{
			setTacticalView = false;
		}
		else
		{
			rotateBaseRotation = rotateBase.transform.rotation;
			setTacticalView = true;
		}
	}
}