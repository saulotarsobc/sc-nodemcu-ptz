import axios from "axios";

setInterval(() => {
  const data = {
    lr: Math.floor(Math.random() * 100) + 0,
    ud: Math.floor(Math.random() * 100) + 0,
    z: Math.floor(Math.random() * 100) + 0,
  };

  axios
    .get("http://192.168.3.19/setPositionServoLR", {
      params: {
        position: data.lr,
      },
    })
    .then(({ data }) => {
      console.log(data);
    })
    .catch((error: Error) => {
      console.log(error.message);
    });
}, 5000);
