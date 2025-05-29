# MakeNTU2025 Group #16


# 作品概念
本作品旨在設計一款能自動跟隨使用者的腳踏車，讓人在不便騎乘時可免去牽車的麻煩，空出雙手，甚至能將物品置於車上運送。此腳踏車具備自主行進與平衡控制能力，期待能在日常通勤、攜帶重物或雨天時提供便利，成為具備智慧移動功能的生活輔助工具。

# 作品架構 [Project Structure](https://app.diagrams.net/#Hpkbbkphey%2FMakeNTU2025%2Fmain%2Fstructure.drawio#%7B%22pageId%22%3A%22IaT-dQrcjwcjiGSIGe-s%22%7D)
- 人像追蹤： 
本系統整合影像辨識與感測技術，透過ESP32進行人像追蹤，搭配裝設於伺服馬達上的ToF測距儀，即時掌握使用者相對位置
- 車體自動平衡：
車體平衡以無刷馬達與驅動器組成的Reaction Wheel，結合陀螺儀與加速度計實現主動平衡控制。
- 自動跟隨：
後輪由無刷馬達驅動，轉向則由步進馬達控制龍頭，協同完成自動移動與跟隨，確保腳踏車平穩且安全地跟隨主人行進。

# 作品動機
我們在校內通勤常需往返於男宿或電機系館與捷運站，攜帶重物或遇雨時不便騎乘，往往須徒步前往公館站，卻在隔日無法取車，造成諸多不便。若腳踏車能自動跟隨並運載行李，將大幅減輕通勤負擔。我們特別以舟山路為模擬場景，考量其坡度與實際需求，作為技術配置與測試依據，希望本作品能成為日常生活的實用輔具。

# Inspirations
- [I made an AUTONOMOUS BICYCLE!](https://youtu.be/kCL2d7wZjU8?si=Q5lIrZy4WpomS9-h) </br>
- [What is the Difference Between Reaction Wheels and Gyroscopes?](https://youtu.be/pJfMFUcquWM?si=ixDk5-67yfu8ZrVs)

# Original Ideas
- focus on rainy days convenicence:
> - Self-balancing with an umbrella holder
> - auto lock/unlock bicycle, so that user do not need to unlock with one hand while holding umbrella
> - allow users to ride bicycle with both hands, make it more secure
> - bicycle head can prevent from overturn and slipping
> - accessibility for stability, direction, and brake
