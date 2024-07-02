
##########

# 학습시킬 데이터 지정
actions = ['2']
seq_length = 60
secs_for_action = 45


cap = cv2.VideoCapture(video)

created_time = int(time.time())
os.makedirs('dataset2', exist_ok=True)


while cap.isOpened():
    for idx, action in enumerate(actions):
        data = []

        ret, img = cap.read()

        img = cv2.flip(img, 1)

        cv2.putText(img, f'Waiting for collecting {action.upper()} action...', org=(10, 30), fontFace=cv2.FONT_HERSHEY_SIMPLEX, fontScale=1, color=(255, 255, 255), thickness=2)
        cv2.imshow('img', img)
        cv2.waitKey(3000)

        start_time = time.time()

        while time.time() - start_time < secs_for_action:
            ret, img = cap.read()
            
            input_img = cv2.resize(img, (width, height), interpolation=cv2.INTER_AREA)
            input_img = input_img.transpose((2, 0, 1))[np.newaxis, ...]
            results = compiled_model([input_img])
            pafs = results[pafs_output_key]
            heatmaps = results[heatmaps_output_key]
            poses, scores = process_results(img, pafs, heatmaps)
            img = draw_poses(img, poses, 0.1)
            
            if poses is not None:
                for pose in poses:
                    points = pose[:,:2]
                    joint = np.zeros((18, 2))
                    for j, lm in enumerate(pose):
                        joint[j] = [points[j,0], points[j,1]]

                    # Compute angles between joints
                    v1 = joint[[ 1, 1, 1, 5, 5, 6, 6, 7, 8,12,11,13,12,14], :] # Parent joint
                    v2 = joint[[ 2, 5, 6, 7,11,12, 8, 9,10,11,13,15,14,16], :] # Child joint
                    v = v2 - v1 # [18, 2]
                    # Normalize v
                    v = v / np.linalg.norm(v, axis=1)[:, np.newaxis]

                    # Get angle using arcos of dot product
                    angle = np.arccos(np.einsum('nt,nt->n',
                    v[[ 0, 0, 1, 1, 3, 3, 2, 2, 6, 6, 4, 4, 5, 5, 9, 9,10,12],:],
                    v[[ 1, 2, 3, 4, 7, 4, 5, 6, 5, 8, 9,10, 9,12,10,12,11,13],:])) #[18,2]
                    angle = np.degrees(angle) # Convert radian to degree
                    angle_label = np.array([angle], dtype=np.float32)
                    angle_label = np.append(angle_label, 2)

                    #d = np.concatenate([joint.flatten(), angle_label])
                    d = angle_label
                    data.append(d)

            cv2.imshow('img', img)
            if cv2.waitKey(1) == ord('q'):
                break

        data = np.array(data)
        print(action, data.shape)
        np.save(os.path.join('dataset2', f'raw_{action}'), data)

        # Create sequence data
        full_seq_data = []
        for seq in range(len(data) - seq_length):
            full_seq_data.append(data[seq:seq + seq_length])

        full_seq_data = np.array(full_seq_data)
        print(action, full_seq_data.shape)
        np.save(os.path.join('dataset2', f'seq_{action}'), full_seq_data)
    break

cap.release()
cv2.destroyAllWindows()