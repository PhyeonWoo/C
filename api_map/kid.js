window.initMap = function () {
    const map = new google.maps.Map(document.getElementById("map"), {
        center: { lat: 37.64802 , lng: 127.064033 },
        zoom: 5
    });
    const malls = [
        { label: "A", name: "연세프렌즈 소아청소년과의원\n", lat: 37.6530156, lng: 127.0613085, phone: "전화번호 : 02-951-7900\n",
          time: "진료시간 : 월~금 09:00 ~ 21:00\n", details: "상세정보 : 서울 노원구 동일로 1392 3층"},

        { label: "B", name: "기쁨 소아청소년과의원\n", lat: 37.6520846, lng: 127.065477, phone: "전화번호 : 02-931-7724\n", 
          time: "진료시간 : 월~금 09:00 ~ 18:00\n",details: "상세정보 : 서울 노원구 동일로216길 70\n"},

        { label: "C", name: "함영백소아과의원\n", lat: 37.650016, lng: 127.0612135, phone: "전화번호 : 02-952-3318\n",
         time: "진료시간 : 월,화,목 09:00 ~ 17:30\n",details:"상세정보 : 서울 노원구 동일로 1361 202동"},

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
