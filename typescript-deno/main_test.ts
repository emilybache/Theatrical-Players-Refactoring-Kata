import { expect } from "@std/expect";
import { statement } from "./main.ts";
import { invoiceSchema } from "./validation/invoice.schema.ts";
import { playReferenceSchema } from "./validation/play.schema.ts";

Deno.test("generate invoice", async () => {
  const invoice = invoiceSchema.parse(
    JSON.parse(await Deno.readTextFile("./assets/invoice.json")),
  );
  const plays = playReferenceSchema.parse(
    JSON.parse(await Deno.readTextFile("./assets/plays.json")),
  );

  expect.setState({
    currentTestName: "generate valid invoice",
    testPath: import.meta.url,
  });
  expect(statement(invoice, plays)).toMatchSnapshot();
});
