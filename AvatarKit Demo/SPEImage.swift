//
//  SPEImage.swift
//  AvatarKit Demo
//
//  Created by Hao Lee on 2017/9/22.
//  Copyright © 2017年 Speed 3D Inc. All rights reserved.
//

import UIKit

extension UIImage {
    func fixOrientation() -> UIImage {
        if self.imageOrientation == .up {
            return self
        }
        
        var transform = CGAffineTransform.identity
        
        switch self.imageOrientation {
        case .down, .downMirrored:
            transform = transform.translatedBy(x: self.size.width, y: self.size.height)
            transform = transform.rotated(by: .pi)
            
        case .left, .leftMirrored:
            transform = transform.translatedBy(x: self.size.width, y: 0)
            transform = transform.rotated(by: .pi / 2)
            
        case .right, .rightMirrored:
            transform = transform.translatedBy(x: 0, y: self.size.height)
            transform = transform.rotated(by: .pi / -2)
            
        case .up, .upMirrored:
            break
        }
        
        switch self.imageOrientation {
        case .upMirrored, .downMirrored:
            transform = transform.translatedBy(x: self.size.width, y: 0)
            transform = transform.scaledBy(x: -1, y: 1)
            
        case .leftMirrored, .rightMirrored:
            transform = transform.translatedBy(x: self.size.height, y: 0)
            transform = transform.scaledBy(x: -1, y: 1)
            
        case .up, .down, .left, .right:
            break
        }
        
        guard let originCGImage = self.cgImage else {
            return self
        }
        
        // Now we draw the underlying CGImage into a new context, applying the transform
        // calculated above.
        guard let ctx = CGContext(data: nil,
                                  width: Int(self.size.width),
                                  height: Int(self.size.height),
                                  bitsPerComponent: originCGImage.bitsPerComponent,
                                  bytesPerRow: 0,
                                  space: originCGImage.colorSpace!,
                                  bitmapInfo: originCGImage.bitmapInfo.rawValue) else {
                                    return self
        }
        
        ctx.concatenate(transform)
        switch self.imageOrientation {
        case .left, .leftMirrored, .right, .rightMirrored:
            ctx.draw(originCGImage, in: CGRect(x: 0, y: 0, width: self.size.height, height: self.size.width))
        default:
            ctx.draw(originCGImage, in: CGRect(x: 0, y: 0, width: self.size.width, height: self.size.height))
        }
        
        // And now we just create a new UIImage from the drawing context
        guard let cgimg = ctx.makeImage() else {
            return self
        }
        let img = UIImage(cgImage: cgimg)
        return img
    }
}
