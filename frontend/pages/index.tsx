import axios from "axios";
import { useCallback, useState } from "react";

export default function Home() {
  const [lrPostion, setLrPostion] = useState(0);

  const setPositionServoLR = useCallback(async () => {
    await fetch("http://192.168.3.19/setPositionServoLR", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({
        position: lrPostion,
      }),
    });
  }, [lrPostion]);

  return (
    <main
      className={`flex min-h-screen flex-col items-center justify-between p-24`}
    >
      <input
        type="range"
        name="range"
        id="range"
        min={0}
        max={100}
        value={lrPostion}
        onChange={(e) => {
          setLrPostion(Number(e.target.value));
          setPositionServoLR();
        }}
      />
      <button
        className="bg-yellow-200 p-5 rounded-lg"
        onClick={setPositionServoLR}
      >
        Position: {lrPostion}
      </button>
    </main>
  );
}
