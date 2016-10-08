# Unity
<br>
<br>
<br>----------------------------------------
<br>----------------------------------------
<br>01.Transform  
<br>
<br>csIdentity - 초기값정렬(localRotation)
<br>csIdentity2 - 초기값정렬(Rotation)
<br>csJump1 - Rigidbody /  velocity
<br>csJump2 - Rigidbody / Addforce
<br>csJump3 - transform.position
<br>csLookAt - 물체 주시 
<br>csMove1 - Translate
<br>csMove2 - update Translate
<br>csMove3 - Rigidbody / velocity
<br>csRotate1 - 오일러 / 쿼터니언 로테이션
<br>csRotate2 - 키입력 로테이션
<br>csRotateAround - 물체 or 지정좌표주위 돌기
<br>csThrow1 - Rigidbody / Addforce 
<br>csThrow2 - Rigidbody / velocity
<br>----------------------------------------
<br>----------------------------------------
<br>02.Collision
<br>
<br>csCollisionCheck - rigidbody, collision , trigger, kinematic
<br>----------------------------------------
<br>----------------------------------------
<br>03.Character Controller // Character Controller 
<br>
<br>csCCMove - CharacterController , TransformDirection -> 월드좌표계 기준으로 변환한 백터
<br>         - OnCollisionEnter -> Rigidbody충돌하면 이벤트
<br>         - OnTriggerEnter ->trigger설정에 따라 이벤트 발생
<br>         - OnControllerColliderHit -> 캐릭터 컨트롤러에 충돌하면 이벤트 발생
<br>----------------------------------------
<br>----------------------------------------
<br>04.Sound
<br>
<br>AudioManager - 싱글톤
<br>csPlay - once play sound
<br>csPlayOneShot - once play sound and can apply volume
<br>csDestoyDelayed - Destroy에서 delay 주기
<br>csWhenDestroyPlay - destory
<br>csAudioManger - single tone으로 객체 넘겨서 플레이
<br>csCheck3DSound - 위치에 따라 사운드 크기가 조정됨
<br>csPlayClipAtPoint - 상동
<br>----------------------------------------
<br>----------------------------------------
<br>05.MouseLook
<br>
<br>csMouseLook - 마우스이동시 카메라 회전(1인칭, FPS등에 사용)
<br>----------------------------------------
<br>----------------------------------------
<br>06.GizmoView
<br>
<br>csGizmoView - 기즈모 보기 편하게 하는 스크립트
<br>----------------------------------------
<br>----------------------------------------
<br>07.RayCast
<br>
<br>csRaycast - 레이케스트 기본
<br>csRaycastAll- 레이케스트 전부
<br>csScreenPointMove - 마우스 클릭을 이용하여 레이케스트를 쏴서 이동
<br>----------------------------------------
<br>----------------------------------------
<br>08.API
<br>
<br>csDistance - 오브젝트 사이의 거리 구하기, 방향구하기, 회전
<br>csRandom - 랜덤숫자생성
<br>csFindChild - 자식오브젝트의 숫자 구하기
<br>----------------------------------------
<br>----------------------------------------
<br>09.Accelerometer
<br>
<br>csKeyMode - 기울이기 및 중력가속도계 사용 (apk로 확인해야함)
<br>----------------------------------------
<br>----------------------------------------
<br>10.Coroutine
<br>
<br>csCoroutine1 - 기본
<br>csCoroutine2 - 비동기식 작업이 끝날때까지 대기하는 코루틴, IEnumerater Start()
<br>             - 웹서버 다운로드
<br>csCoroutine3 - 2 & check
<br>----------------------------------------
<br>----------------------------------------
<br>11.LoadScene
<br>
<br>canvas 기능
<br>LoadLevel -> using UnityEngine.SceneManagement // Scenemanager.LoadScene 바뀜
<br>
<br>csSceneTrans1 - 기본
<br>csSceneTrans2 - Scene의 라이프사이클
<br>csSceneTrans3 - 옵션주기
<br>----------------------------------------
<br>----------------------------------------
<br>12.CallFunc
<br>
<br>csGameManager - 다른 스크립트의 public, private, static 호출하기
<br>----------------------------------------
<br>----------------------------------------
<br>13.PlayerPrefs
<br>
<br>csGameManager - 기본
<br>----------------------------------------
<br>----------------------------------------
<br>14.uGUI
<br>
<br>csButton - 버튼클릭해서 Text 바꾸기
<br>Toggle
<br>RadioBox
<br>Slider
<br>Input
<br>ScrollRect
<br>ScrollBar
<br>ScrollView
<br>----------------------------------------
<br>----------------------------------------
<br>15.MaterialChange
<br>
<br>csWomanMaterialSet - 인스펙터에서 직접
<br>csDynamicChange - 동적 변환
<br>csResourcesLoad - ResourceLoad를 통한 변환
<br>----------------------------------------
<br>----------------------------------------
<br>16.Animation
<br>
<br>csLegacy -  
<br>csMecanim - 
<br>----------------------------------------
<br>----------------------------------------
<br>17.Joystick
<br>
<br>csPlayerController - 조이스틱 기본
<br>----------------------------------------
<br>----------------------------------------