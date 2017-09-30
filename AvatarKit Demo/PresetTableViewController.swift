//
//  PresetTableViewController.swift
//  AvatarKit Demo
//
//  Created by Hao Lee on 2017/9/28.
//  Copyright © 2017年 Speed 3D Inc. All rights reserved.
//

import UIKit
import AvatarKit

class PresetTableViewController: UITableViewController {

    var presetType: AVKPresetType?
    var gender = AVKGender.male
    var selectPresetClosure: ((AVKPreset) -> Void)?
    
    var presets: [AVKPreset] = []
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.loadPresetData()
        
        self.clearsSelectionOnViewWillAppear = true
    }
    
    func loadPresetData() {
        guard let presetType = self.presetType else {
            return
        }
        
        self.presets = AVKPreset.getPresets(for: presetType, gender: self.gender)
        
        self.tableView.reloadData()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    // MARK: - action
    
    @IBAction func closeAction(_ sender: UIBarButtonItem) {
        self.dismiss(animated: true, completion: nil)
    }
    
    // MARK: - Table view data source
    
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.presets.count
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "presetCell", for: indexPath) as! PresetTableViewCell
        
        cell.nameLabel?.text = self.presets[indexPath.row].name
        
        let imageView = cell.previewImageView
        
        imageView?.image = nil
        
        self.presets[indexPath.row].observeDownloadedPreviewImage { (preset, error) in
            DispatchQueue.main.asyncAfter(deadline: .now() + 0.01, execute: {
                guard let cell = tableView.cellForRow(at: indexPath) as? PresetTableViewCell else {
                    return
                }
                
                cell.previewImageView?.image = preset.previewImage
            })
        }
        
        return cell
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        self.selectPresetClosure?(self.presets[indexPath.row])
        
        self.dismiss(animated: true, completion: nil)
    }

}

class PresetTableViewCell: UITableViewCell {
    @IBOutlet var previewImageView: UIImageView?
    @IBOutlet var nameLabel: UILabel?
}
