/** NFCEncodingTests.re
 ** Copyright 2019 NineFX Inc.
 ** Justin Baum
 ** unorm NFC Encoding Tests
 ** 15 May 2019
 */
open Jest;
open Expect;

let encodingTest1 = () => {
  let str = {j|¡™£¢∞§¶•ªº–≠œ∑´®†¥¨ˆøπ““‘«åß∂ƒ©˙∆˚¬…æ≈ç√∫˜µ≤≥÷⁄€‹›ﬁﬂ‡°·‚—±Œ„´‰ˇÁØ∏”’»/* ÍÎ˝ÓÔÒÚÆ¸˛Ç◊˜Â¯˘¿1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./|j};
  expect(
    {j|¡™£¢∞§¶•ªº–≠œ∑´®†¥¨ˆøπ““‘«åß∂ƒ©˙∆˚¬…æ≈ç√∫˜µ≤≥÷⁄€‹›ﬁﬂ‡°·‚—±Œ„´‰ˇÁØ∏”’»/* ÍÎ˝ÓÔÒÚÆ¸˛Ç◊˜Â¯˘¿1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./|j},
  )
  |> toEqual(PrecisUnorm.nfcString(str));
};

let () = {
  describe("NFC Encoding Tests ", () =>
    test("NFC Test 1", encodingTest1)
  );
};
