import z from "zod";

const playDescriptionSchema = z.object({
  name: z.string(),
  type: z.string(),
});

export const playReferenceSchema = z.object({
  hamlet: playDescriptionSchema,
  "as-like": playDescriptionSchema,
  othello: playDescriptionSchema,
});

export type PlayReference = z.infer<typeof playReferenceSchema>;
