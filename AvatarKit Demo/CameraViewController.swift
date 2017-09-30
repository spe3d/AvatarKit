//
//  CameraViewController.swift
//  AvatarKit Demo
//
//  Created by Hao Lee on 2017/9/22.
//  Copyright © 2017年 Speed 3D Inc. All rights reserved.
//

import UIKit
import AVFoundation
import MBProgressHUD
import AvatarKit
import SceneKit

class CameraViewController: ViewController, AVCaptureMetadataOutputObjectsDelegate, UIImagePickerControllerDelegate, UINavigationControllerDelegate {

    @IBOutlet weak var previewView: UIView!
    
    @IBOutlet weak var changeCameraButton: UIButton!
    
    var delegate: CameraViewControllerDelegate?
    
    //Session
    lazy var captureSession : AVCaptureSession = {
        let captureSession = AVCaptureSession()
        
        if captureSession.canAddOutput(self.capturePhotoOutput) {
            captureSession.addOutput(self.capturePhotoOutput)
        }
        
        self.captureVideoPreviewLayer.session = captureSession
        self.captureVideoPreviewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill
        
        self.captureVideoPreviewLayer.frame = UIScreen.main.bounds
        self.previewView.layer.insertSublayer(self.captureVideoPreviewLayer, at: 0)
        
        return captureSession
    }()
    
    //Output
    private let capturePhotoOutput : AVCapturePhotoOutput = {
        let capturePhotoOutput = AVCapturePhotoOutput()
        capturePhotoOutput.isHighResolutionCaptureEnabled = true
        return capturePhotoOutput
    }()
    
    private let captureVideoDataOutput = AVCaptureVideoDataOutput()
    private var captureVideoDataOutputQueue = DispatchQueue(label: "captureVideoDataOutputQueue")
    
    //PreviewLayer
    let captureVideoPreviewLayer = AVCaptureVideoPreviewLayer()
    
    lazy var availableCameraInput : [AVCaptureDevicePosition : AVCaptureDeviceInput] = {
        
        var availableCameraInput = [AVCaptureDevicePosition : AVCaptureDeviceInput]()
        
        
        if let frontCamera = AVCaptureDeviceDiscoverySession(deviceTypes: [AVCaptureDeviceType.builtInWideAngleCamera], mediaType: nil, position: AVCaptureDevicePosition.front).devices.first {
            if frontCamera.hasMediaType(AVMediaTypeVideo) {
                do {
                    let cameraInput = try AVCaptureDeviceInput(device: frontCamera)
                    availableCameraInput[.front] = cameraInput
                }
                catch {}
            }
        }
        
        if let backCamera = AVCaptureDeviceDiscoverySession(deviceTypes: [AVCaptureDeviceType.builtInWideAngleCamera], mediaType: nil, position: AVCaptureDevicePosition.back).devices.first {
            if backCamera.hasMediaType(AVMediaTypeVideo) {
                do {
                    let cameraInput = try AVCaptureDeviceInput(device: backCamera)
                    availableCameraInput[.back] = cameraInput
                }
                catch {}
            }
        }
        
        return availableCameraInput
    }()
    
    var devicePosition : AVCaptureDevicePosition = .unspecified {
        didSet {
            
            self.captureSession.stopRunning()
            
            for input in self.captureSession.inputs {
                if let cameraInput = input as? AVCaptureDeviceInput {
                    self.captureSession.removeInput(cameraInput)
                }
            }
            
            if self.devicePosition != .unspecified {
                
                var deviceInput : AVCaptureDeviceInput? = nil
                
                if let input = self.availableCameraInput[self.devicePosition] {
                    deviceInput = input
                }
                else {
                    self.showAlertCameraUnavailable()
                }
                
                if let deviceInput = deviceInput {
                    self.captureSession.addInput(deviceInput)
                    self.captureSession.startRunning()
                }
            }
        }
    }
    
    var showCameraDeniedMessage = false
    
    var faceImage: UIImage?
    
    var gender = AVKGender.male
    
    var hud: MBProgressHUD?
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        if AVCaptureDevice.authorizationStatus(forMediaType: AVMediaTypeVideo) == .authorized {
            self.startPreview()
        }
        else {
            AVCaptureDevice.requestAccess(forMediaType: AVMediaTypeVideo, completionHandler: { (granted) -> Void in
                DispatchQueue.main.async {
                    if granted {
                        self.startPreview()
                    }
                    else {
                        self.showAlertCameraUnavailable()
                    }
                }
            })
        }
    }
    
    override func viewDidDisappear(_ animated: Bool) {
        self.devicePosition = .unspecified //使相機關閉
        super.viewDidDisappear(animated)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func startPreview() {
        if self.availableCameraInput.count <= 1 {
            self.navigationItem.rightBarButtonItem = nil
        }
        
        if let _ = self.availableCameraInput[.front] {
            self.devicePosition = .front
        }
        else {
            if let _ = self.availableCameraInput[.back] {
                self.devicePosition = .back
            }
            else {
                self.showAlertCameraUnavailable()
            }
        }
    }
    
    func showAlertCameraUnavailable() {
        let alertView = UIAlertController(title: NSLocalizedString("Error", comment: ""), message: nil, preferredStyle: .alert)
        
        let openSettingsURL = URL(string: UIApplicationOpenSettingsURLString)
        
        alertView.addAction(UIAlertAction(title: NSLocalizedString("Go", comment: ""), style: UIAlertActionStyle.default, handler: { (action :UIAlertAction) -> Void in
            UIApplication.shared.open(openSettingsURL!)
        }))
        
        alertView.message = NSLocalizedString("It looks like your privacy settings are preventing us from accessing your camera to do barcode scanning. You can fix this by doing the following:\n\n1. Touch the Go button below to open the Settings app.\n\n2. Touch Privacy.\n\n3. Turn the Camera on.\n\n4. Open this app and try again.", comment: "")
        
        alertView.addAction(UIAlertAction(title: NSLocalizedString("OK", comment: ""), style: .cancel, handler: nil))
        
        self.present(alertView, animated: true, completion: nil)
    }
    
    func showLoadingView() {
        self.captureSession.stopRunning()
        self.captureVideoPreviewLayer.isHidden = true
        self.previewView.layer.contents = self.faceImage?.cgImage
        
        let view: UIView = self.view.window ?? self.view
        let hud = MBProgressHUD(view: view)
        hud.label.text = "Loading..."
        
        view.addSubview(hud)
        hud.show(animated: true)
        
        self.hud = hud
    }
    
    func createAvatar() {
        if let faceImage = self.faceImage {
            AVKAvatarCreator().createAvatar(with: self.gender, face: faceImage, successBlock: { (avatarController) -> Void in
                self.hud?.hide(animated: true)
                
                self.delegate?.cameraViewController(self, didCreateAvatarController: avatarController)
                
                self.dismiss(animated: true, completion: nil)
            }, failureBlock: { (error) -> Void in
                self.hud?.hide(animated: true)
                
                let view: UIView = self.view.window ?? self.view
                let hud = MBProgressHUD(view: view)
                hud.mode = .text
                hud.label.text = error.localizedDescription
                hud.offset = CGPoint(x: 0, y: MBProgressMaxOffset)
                hud.isUserInteractionEnabled = false
                view.addSubview(hud)
                hud.show(animated: true)
                hud.hide(animated: true, afterDelay: 2)
                
                self.dismiss(animated: true, completion: nil)
            })
        }
    }
    
    // MARK: - action
    
    @IBAction func cancelAction() {
        self.dismiss(animated: true, completion: nil)
    }
    
    @IBAction func albumAction() {
        let imagePickerController = UIImagePickerController()
        imagePickerController.delegate = self
        imagePickerController.sourceType = .photoLibrary
        
        self.present(imagePickerController, animated: true, completion: nil)
    }
    
    @IBAction func shutterAction() {
        let settings = AVCapturePhotoSettings()
        settings.isHighResolutionPhotoEnabled = true
        self.capturePhotoOutput.capturePhoto(with: settings, delegate: self)
    }
    
    @IBAction func changeCameraAction() {
        if self.devicePosition == .front {
            self.devicePosition = .back
            self.changeCameraButton.setTitle("Front", for: UIControlState())
        }
        else {
            self.devicePosition = .front
            self.changeCameraButton.setTitle("Back", for: UIControlState())
        }
    }
    
    // MARK: - UIImagePickerControllerDelegate
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [String : Any]) {
        
        if let image = info[UIImagePickerControllerOriginalImage] as? UIImage {
            self.faceImage = image.fixOrientation()
            self.createAvatar()
        }
        
        self.dismiss(animated: true) { () -> Void in
            self.showLoadingView()
        }
    }
    
    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        picker.dismiss(animated: true, completion: nil)
    }
}

extension CameraViewController: AVCapturePhotoCaptureDelegate {
    func capture(_ output: AVCapturePhotoOutput, didFinishProcessingPhotoSampleBuffer photoSampleBuffer: CMSampleBuffer?, previewPhotoSampleBuffer: CMSampleBuffer?, resolvedSettings: AVCaptureResolvedPhotoSettings, bracketSettings: AVCaptureBracketedStillImageSettings?, error: Error?) {
        
        if let photoSampleBuffer = photoSampleBuffer,
            let imageData = AVCapturePhotoOutput.jpegPhotoDataRepresentation(forJPEGSampleBuffer: photoSampleBuffer,
                                                                             previewPhotoSampleBuffer: nil),
            var image = UIImage(data: imageData)?.fixOrientation(),
            var ciImage = CIImage(image: image) {
            
            let filters = ciImage.autoAdjustmentFilters(options: nil)
            
            for filter in filters {
                if filter.name == "CIFaceBalance" {
                    filter.setValue(ciImage, forKey: kCIInputImageKey)
                    if let image = filter.outputImage {
                        ciImage = image
                    }
                    
                    break
                }
            }
            
            let context = CIContext(options: nil)
            if let cgImage = context.createCGImage(ciImage, from: ciImage.extent) {
                image = UIImage(cgImage: cgImage)
            }
            
            DispatchQueue.global(qos: .background).async {
                UIImageWriteToSavedPhotosAlbum(image, nil, nil, nil)
            }
            self.faceImage = image
            
            self.showLoadingView()
            
            self.createAvatar()
        }
        else {
            print("not image input")
        }
    }
}

protocol CameraViewControllerDelegate: NSObjectProtocol {
    func cameraViewController(_ viewController: CameraViewController, didCreateAvatarController avatarController: AVKAvatarController)
}
