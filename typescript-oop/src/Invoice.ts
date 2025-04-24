import { Performance } from "./Performance";

export class Invoice {
  constructor(public customer: string, public performances: Performance[]) {}
}
