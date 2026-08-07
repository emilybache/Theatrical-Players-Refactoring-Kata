import { expect } from "@std/expect";
import { statement } from "./main.ts";
import { invoiceSchema } from "./validation/invoice.schema.ts";
import { playReferenceSchema } from "./validation/play.schema.ts";

Deno.test({
  name: "generate invoice",
  fn: async () => {
    const invoice = invoiceSchema.parse(
      JSON.parse(await Deno.readTextFile("./assets/invoice.json")),
    );
    const plays = playReferenceSchema.parse(
      JSON.parse(await Deno.readTextFile("./assets/plays.json")),
    );

    expect(statement(invoice, plays), "the content of the file");
  },
});
