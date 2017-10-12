//
//  AvatarViewController.swift
//  AvatarKit Demo
//
//  Created by Hao Lee on 2017/9/21.
//  Copyright © 2017年 Speed 3D Inc. All rights reserved.
//

import UIKit
import SceneKit
import AvatarKit
import MBProgressHUD

class AvatarViewController: ViewController {
    
    @IBOutlet var avatarView: SCNView!
    
    @IBOutlet var cleanButton: UIButton!
    
    var avatarController: AVKAvatarController?
    
    var gender = AVKGender.male

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func assign(avatarController: AVKAvatarController) {
        let scene = SCNScene()
        self.avatarView.scene = scene
        
        self.avatarController = avatarController
        
        self.avatarView.scene?.rootNode.addChildNode(avatarController.sceneNode)
        
        self.setupDefaultCamera()
    }
    
    func setupDefaultCamera() {
        let camera = AVKAvatarController.defaultCameraNode
        
        self.avatarView.scene?.rootNode.addChildNode(camera)
        
        self.avatarView.pointOfView = camera
    }
    
    func localAvatarPath() -> String {
        return FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)[0].appendingPathComponent("AvatarController").path
    }
    
    // MARK: - action
    
    @IBAction func facialAction(sender: UIButton) {
        var array: [NSNumber] = Array(repeating: 0, count: 26)
        array[25] = 1
        self.avatarController?.setFacialWithWeights(array)
    }
    
    @IBAction func showBackgroundAction(sender: UIButton) {
        self.avatarView.scene?.rootNode.childNode(withName: "background", recursively: true)?.removeFromParentNode()

        guard let avatarController = self.avatarController else {
            return
        }

        let scale = UIScreen.main.nativeScale / CGFloat(avatarController.sceneNode.childNode(withName: "Hips", recursively: true)!.scale.x)
        let image = UIImage(named: "mvp_bg")!
        let scenery = SCNPlane(width: image.size.width / scale, height: image.size.height / scale)
        scenery.firstMaterial?.diffuse.contents = image
        let node = SCNNode(geometry: scenery)
        node.name = "background"
        node.position = SCNVector3Make(0, 130, -130)
        self.avatarView.scene?.rootNode.addChildNode(node)
    }

    @IBAction func getDefaultAvatarAction(sender: UIButton) {
        let avatarController = AVKAvatarController(genderOfDefaultAvatar: self.gender)

        self.assign(avatarController: avatarController)
    }
    
    @IBAction func saveAvatarAction(sender: UIButton) {
        guard let avatarController = self.avatarController else {
            return
        }
        
        let _ = NSKeyedArchiver.archiveRootObject(avatarController, toFile: self.localAvatarPath())
    }
    
    @IBAction func loadAvatarAction(sender: UIButton) {
        guard let avatarController = NSKeyedUnarchiver.unarchiveObject(withFile: self.localAvatarPath()) as? AVKAvatarController else {
            return
        }
        
        if avatarController.isWornPresets {
            self.assign(avatarController: avatarController)
        }
        else {
            avatarController.observeAvatarHasWornPresets({ (avatarSceneNode) in
                self.assign(avatarController: avatarController)
            })
        }
    }
    
    @IBAction func cleanAvatarAction(sender: UIButton) {
        guard let rootNode = self.avatarView.scene?.rootNode else {
            return
        }
        
        for node in rootNode.childNodes {
            node.removeFromParentNode()
        }
        
        self.avatarController = nil
        self.avatarView.scene = nil
    }
    
    @IBAction func switchGenderAction(sender: UISegmentedControl) {
        switch sender.selectedSegmentIndex {
        case 0:
            self.gender = .male
        case 1:
            self.gender = .female
        default: break
        }
        
        self.cleanButton?.sendActions(for: .touchUpInside)
    }
    
    @IBAction func createCustomFaceAction(sender: UIButton) {
        if let controller = self.storyboard?.instantiateViewController(withIdentifier: "CameraViewController") as? CameraViewController {
            controller.modalTransitionStyle = .crossDissolve
            controller.gender = self.gender
            controller.delegate = self
            self.present(controller, animated: true, completion: nil)
        }
    }
    
    // MARK: change preset
    
    @IBAction func changeHairAction(sender: UIButton) {
        guard let navigationController = self.storyboard?.instantiateViewController(withIdentifier: "PresetNavigationController") as? UINavigationController else {
            return
        }
        
        guard let controller = navigationController.viewControllers[0] as? PresetTableViewController else {
            return
        }
        
        controller.gender = self.gender
        controller.presetType = .hair
        controller.selectPresetClosure = {(preset) -> Void in
            let hud = MBProgressHUD(view: self.view)
            hud.label.text = "Downloading..."
            
            self.view.addSubview(hud)
            hud.show(animated: true)
            self.avatarController?.setHair(preset, completionHandler: { (success, error) in
                hud.hide(animated: true)
                
                if let error = error {
                    NSLog(error.localizedDescription)
                }
                
                NSLog("\(success)")
            })
        }
        controller.title = "Hair"
        self.present(navigationController, animated: true, completion: nil)
    }
    
    @IBAction func changeSuitAction(sender: UIButton) {
        guard let navigationController = self.storyboard?.instantiateViewController(withIdentifier: "PresetNavigationController") as? UINavigationController else {
            return
        }
        
        guard let controller = navigationController.viewControllers[0] as? PresetTableViewController else {
            return
        }
        
        controller.gender = self.gender
        controller.presetType = .suit
        controller.selectPresetClosure = {(preset) -> Void in
            let hud = MBProgressHUD(view: self.view)
            hud.label.text = "Downloading..."
            
            self.view.addSubview(hud)
            hud.show(animated: true)
            self.avatarController?.setSuit(preset, completionHandler: { (success, error) in
                hud.hide(animated: true)
                
                if let error = error {
                    NSLog(error.localizedDescription)
                }
                
                NSLog("\(success)")
            })
        }
        controller.title = "Suit"
        self.present(navigationController, animated: true, completion: nil)
    }
    
    @IBAction func changeMotionAction(sender: UIButton) {
        guard let navigationController = self.storyboard?.instantiateViewController(withIdentifier: "PresetNavigationController") as? UINavigationController else {
            return
        }
        
        guard let controller = navigationController.viewControllers[0] as? PresetTableViewController else {
            return
        }
        
        controller.gender = self.gender
        controller.presetType = .motion
        controller.selectPresetClosure = {(preset) -> Void in
            let hud = MBProgressHUD(view: self.view)
            hud.label.text = "Downloading..."
            
            self.view.addSubview(hud)
            hud.show(animated: true)
            self.avatarController?.setMotion(preset, completionHandler: { (success, error) in
                hud.hide(animated: true)
                
                if let error = error {
                    NSLog(error.localizedDescription)
                }
                
                NSLog("\(success)")
            })
        }
        controller.title = "Motion"
        self.present(navigationController, animated: true, completion: nil)
    }
    
    @IBAction func changeAccessoryAction(sender: UIButton) {
        guard let navigationController = self.storyboard?.instantiateViewController(withIdentifier: "PresetNavigationController") as? UINavigationController else {
            return
        }
        
        guard let controller = navigationController.viewControllers[0] as? PresetTableViewController else {
            return
        }
        
        controller.gender = self.gender
        controller.presetType = .accessory
        controller.selectPresetClosure = {(preset) -> Void in
            let hud = MBProgressHUD(view: self.view)
            hud.label.text = "Downloading..."
            
            self.view.addSubview(hud)
            hud.show(animated: true)
            self.avatarController?.setAccessory(preset, completionHandler: { (success, error) in
                hud.hide(animated: true)
                
                if let error = error {
                    NSLog(error.localizedDescription)
                }
                
                NSLog("\(success)")
            })
        }
        controller.title = "Accessory"
        self.present(navigationController, animated: true, completion: nil)
    }
    
    @IBAction func removeAccessoryAction(sender: UIButton) {
        self.avatarController?.setAccessory(nil, completionHandler: { (_, _) in
            
        })
    }
    
}

extension AvatarViewController: CameraViewControllerDelegate {
    func cameraViewController(_ viewController: CameraViewController, didCreateAvatarController avatarController: AVKAvatarController) {
        self.assign(avatarController: avatarController)
    }
    
}
