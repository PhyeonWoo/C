window.initMap = function () {
    const map = new google.maps.Map(document.getElementById("map"), {
        center: { lat: 37.64802 , lng: 127.064033 },
        zoom: 5
    });
    const malls = [
        { label: "A", name: "허브치과\n", lat: 37.654442, lng: 127.059903, phone: "전화번호 : 02-933-2854\n",
          time: "진료시간 : 월~금 09:30 ~ 18:30\n", details: "서울 노원구 노해로 467 교보빌딩 11"},

        { label: "B", name: "서울 더 플랜 치과\n", lat: 37.654594, lng: 127.062985, phone: "전화번호 : 02-951-2828\n", 
          time: "진료시간 : 월,수,금 10:00 ~ 19:30\n",details: "상세정보 : 서울 노원구 노해로 494 고려빌딩 2층\n"},

        { label: "C", name: "서울 열린치과의원\n", lat: 37.6523827, lng: 127.0615286, phone: "전화번호 : 02-951-2828\n",
         time: "진료시간 : 월,수,금,토 10:00 ~ 19:00\n",details:"서울 노원구 동일로 1384"},

        { label: "D", name: "노원 아이디치과\n", lat: 37.653204, lng: 127.061297, phone: "전화번호 : 02-3496-5680\n",
         time: "진료시간 : 화,수,금 : 10:00 ~ 19:00\n",details:"서울 노원구 동일로 1396 중원빌딩 2층"},
    ];
    const bounds = new google.maps.LatLngBounds();
    const infoWindow = new google.maps.InfoWindow();
    
    malls.forEach(({ label, name, lat, lng, phone,time,details }) => {
        const marker = new google.maps.Marker({
            position: { lat, lng },
            label,
            map
        });
        bounds.extend(marker.position);
        
        marker.addListener("click", () => {
            map.panTo(marker.position);
            infoWindow.setContent(`<strong><span style="font-size:18px;">${name}</strong><br><span style="font-size:13px;">${phone}<br><span style="font-size:13px;">${time}<br><span style="font-size:13px;">${details}`);
            infoWindow.open({
                anchor: marker,
                map
            });
        });
    });

    map.fitBounds(bounds);
};
  