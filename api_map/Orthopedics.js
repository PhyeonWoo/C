window.initMap = function () {
    const map = new google.maps.Map(document.getElementById("map"), {
        center: { lat: 37.64802 , lng: 127.064033 },
        zoom: 5
    });
    const malls = [
        { label: "A", name: "이홍섭정형외과\n", lat: 37.648194, lng: 127.062132, phone: "전화번호 : 010-1234-5678\n",
          time: "진료시간 : 09:00~15:00\n", details: "상세정보 : 서울 노원구 동일로 1335 대원빌"},

        { label: "B", name: "김앤조서울 정형외과\n", lat: 37.660012, lng: 127.063500, phone: "전화번호 : 010-6933-7080\n", 
          time: "진료시간 : 월~금 09:00 ~ 19:00\n",details: "상세정보 : 서울 노원구 노원로 26길 181 청자빌딩 2~5층\n"},

        { label: "C", name: "노원 서울스카이 정형외과\n", lat: 37.653830, lng: 127.060245, phone: "전화번호 : 02-2039-0911\n",
         time: "진료시간 : 월~목 09:00 ~ 20:00\n",details:"서울 노원구 동일로 1405, 7층"},

        { label: "D", name: "중계넘버원 정형외과\n", lat: 37.651174, lng: 127.076461, phone: "전화번호 : 02-935-5555\n",
         time: "진료시간 :월~금 09:00 ~ 19:00\n",details:"서울 노원구 한글비석로 263 성모빌딩 2층"},
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
            infoWindow.setContent(`<strong>${name}</strong><br>${phone}<br>${time}<br>${details}`);
            infoWindow.open({
                anchor: marker,
                map
            });
        });
    });

    map.fitBounds(bounds);
};
  