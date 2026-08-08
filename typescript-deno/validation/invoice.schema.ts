import z from "zod";
import { playReferenceSchema } from "./play.schema.ts";

const performanceSchema = z.object({
  playID: playReferenceSchema.keyof(),
  audience: z.number().min(1),
});

export const invoiceSchema = z.object({
  customer: z.string(),
  performances: z.array(
    performanceSchema,
  ),
});

export type Invoice = z.infer<typeof invoiceSchema>;
