using UnityEngine;
using System.Collections;

public class GyroCamera3 : MonoBehaviour {

    private Gyroscope gyro;
    private bool gyroSupported;
    private Quaternion rotFix;

    [SerializeField]
    private Transform worldObj;
    private float startY;

    void Start() {
        gyroSupported = SystemInfo.supportsGyroscope;

        GameObject camParent = new GameObject("camParent");
        camParent.transform.position = transform.position;
        transform.parent = camParent.transform;

        if (gyroSupported) {
            gyro = Input.gyro;
            gyro.enabled = true;

            camParent.transform.rotation = Quaternion.Euler(90f, 180f, 0f);
            rotFix = new Quaternion(0, 0, 1, 0);
        }
    }

    void Update() {
        if(gyroSupported && startY == 0) {
            ResetGyroRotation();
        }
        if (gyroSupported) {
            transform.localRotation = gyro.attitude * rotFix;
        }
    }

    void ResetGyroRotation() {
        startY = transform.eulerAngles.y;
        worldObj.rotation = Quaternion.Euler(0f, startY, 0f);
    }

}
